// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <string>
#include <sstream>

#include "clang.hpp"

#include "arrow/pass/declare.hpp"
#include "arrow/log.hpp"

using arrow::pass::Declare;
using arrow::ptr;
using arrow::Span;
using arrow::Position;
using arrow::make;
using arrow::GContext;
namespace ir = arrow::ir;
namespace ast = arrow::ast;

CXChildVisitResult cx_visit(
  CXCursor cursor, CXCursor parent, CXClientData clientData);

static std::unordered_map<std::string, std::string> _c_typenames = {
  {"unsigned char",      "c_uchar"},
  {"unsigned short",     "c_ushort"},
  {"unsigned int",       "c_uint"},
  {"unsigned long",      "c_ulong"},
  {"unsigned long long", "c_ullong"},
  {"char",               "c_char"},
  {"signed char",        "c_char"},
  {"short",              "c_short"},
  {"int",                "c_int"},
  {"long",               "c_long"},
  {"long long",          "c_llong"},
  {"long double",        "c_ldouble"},
  {"double",             "c_double"},
  {"float",              "c_float"},
};

static std::unordered_map<std::string, ptr<ir::Type>> _c_types;

static CXChildVisitResult _ctype_visit(
  CXCursor cursor, CXCursor parent, CXClientData clientData
) {
  auto c_kind = clang_getCursorKind(cursor);
  auto c_name = clang_getCString(clang_getCursorSpelling(cursor));

  switch (c_kind) {
  case CXCursor_TypedefDecl: {
    auto c_type = clang_getCanonicalType(clang_getCursorType(cursor));

    auto size_bytes = clang_Type_getSizeOf(c_type);
    auto size_bits = size_bytes * 8;

    ptr<ir::Type> item;
    switch (c_type.kind) {
    case CXType_UChar:
    case CXType_Char_U:
    case CXType_UShort:
    case CXType_UInt:
    case CXType_ULong:
    case CXType_ULongLong:
    case CXType_UInt128:
      item = arrow::make<ir::TypeInteger>(false, size_bits);
      break;

    case CXType_SChar:
    case CXType_Char_S:
    case CXType_Short:
    case CXType_Int:
    case CXType_Long:
    case CXType_LongLong:
    case CXType_Int128:
      item = arrow::make<ir::TypeInteger>(true, size_bits);
      break;

    default:
      item = nullptr;
    }

    _c_types[c_name] = item;
  } return CXChildVisit_Continue;

  default:
    break;
  }

  return CXChildVisit_Continue;
}

static void _require_c_types(GContext& ctx) {
  if (_c_types.size() == 0) {
    // Initialize clang
    auto cx = clang_createIndex(1, 1);

    // Declare C file with typedefs to primitive types
    std::stringstream stream;
    for (auto const& ref : _c_typenames) {
      // Skip the stand-alone char type (its doubled because C is weird)
      if (ref.first == "char") continue;

      stream << "typedef ";
      stream << ref.first;
      stream << " ";
      stream << ref.second;
      stream << ";\n";
    }

    auto buffer = stream.str();
    auto file = CXUnsavedFile{"main.c", buffer.c_str(), buffer.size()};

    auto tu = clang_parseTranslationUnit(cx, "main.c", nullptr, 0, &file, 1,
      CXTranslationUnit_DetailedPreprocessingRecord |
      CXTranslationUnit_SkipFunctionBodies);

    // Visit!
    clang_visitChildren(clang_getTranslationUnitCursor(tu),
      &_ctype_visit, nullptr);

    // Dispose: clang
    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(cx);
  }

  // Emplace into scope
  for (auto const& ref : _c_typenames) {
    if (_c_types[ref.second]) {
      ctx.scope->put(ref.second, _c_types[ref.second]);
    }
  }
}

static std::string _c_typename(CXType c_type) {
  // Ensure we're dealing with a canoncial type
  c_type = clang_getCanonicalType(c_type);

  auto c_typename = std::string(clang_getCString(
    clang_getTypeSpelling(c_type)));

  if (clang_isConstQualifiedType(c_type)) {
    // Remove 'const ' from typename
    c_typename = c_typename.substr(6);
  }

  // Determine typename
  auto typename_ = _c_typenames[c_typename];
  if (typename_ == "") {
    // fmt::print("primitive C type failed to match: {}\n", c_typename);
    return "";
  }

  // Add C basic type
  return typename_;
}

static ptr<ir::Type> _c_type(CXType type) {
  auto ref = clang_getCanonicalType(type);

  if (ref.kind == CXType_Pointer) {
    auto pointee = _c_type(clang_getPointeeType(type));
    if (!pointee) return nullptr;

    return make<ir::TypePointer>(nullptr, pointee);
  }

  if (ref.kind == CXType_Void) {
    return make<ir::TypeUnit>();
  }

  auto typename_ = _c_typename(ref);
  if (typename_ == "") return nullptr;

  return _c_types[typename_];
}

static CXChildVisitResult _cx_visit(
  CXCursor cursor, CXCursor parent, CXClientData clientData
) {
  auto ctx = reinterpret_cast<GContext*>(clientData);
  auto c_kind = clang_getCursorKind(cursor);
  auto c_name = clang_getCString(clang_getCursorSpelling(cursor));

  ptr<ir::Item> item;

  switch (c_kind) {
  case CXCursor_TypedefDecl: {
    auto c_type = _c_type(clang_getCursorType(cursor));
    if (!c_type) break;

    // Make: Alias
    item = make<ir::TypeAlias>(nullptr, c_name, c_type);
  } break;

  case CXCursor_FunctionDecl: {
    auto ref = clang_getCursorType(cursor);

    // Do: Result Type
    auto result = _c_type(clang_getCursorResultType(cursor));
    if (!result) break;

    // Do: Parameters
    std::vector<ptr<ir::Type>> parameters;
    bool failed = false;
    for (auto i = 0; i < clang_getNumArgTypes(ref); ++i) {
      auto atype = _c_type(clang_getArgType(ref, i));
      if (!atype) {
        // fmt::print("Argument Type: {}\n", clang_getCString(
        //   clang_getTypeSpelling(clang_getArgType(ref, i))));

        failed = true;
        break;
      }

      parameters.push_back(atype);
    }

    if (failed) break;

    // Make: Function Type
    // TODO: ABI
    ptr<ir::TypeExternFunction> type(new ir::TypeExternFunction(
      nullptr, clang_isFunctionTypeVariadic(ref),
      "C", parameters, result));

    // Make: External Function
    item = make<ir::ExternFunction>(nullptr, ctx->modules.back(), c_name,
      type);
  } break;

  default:
    break;
  }

  if (item) {
    // arrow::Log::get().info("c: {} ({})", c_name, c_kind);
    ctx->scope->put(c_name, item);
  } else {
    // arrow::Log::get().warn("unhandled: {} ({})", c_name, c_kind);
  }

  return CXChildVisit_Continue;
}

void Declare::visit_cinclude(ptr<ast::CInclude> x) {
  // Require (import) C primitive types
  _require_c_types(_ctx);

  // Declare C file that includes the requested include
  std::stringstream stream;
  stream << "#include <" << x->source << ">\n";

  // Initialize clang
  auto cx = clang_createIndex(1, 1);
  auto buffer = stream.str();
  auto file = CXUnsavedFile{"main.c", buffer.c_str(), buffer.size()};

  auto tu = clang_parseTranslationUnit(cx, "main.c", nullptr, 0, &file, 1,
    CXTranslationUnit_DetailedPreprocessingRecord |
    CXTranslationUnit_SkipFunctionBodies);

  // Visit!
  clang_visitChildren(clang_getTranslationUnitCursor(tu),
    &_cx_visit, &_ctx);

  // Dispose: clang
  clang_disposeTranslationUnit(tu);
  clang_disposeIndex(cx);
}
