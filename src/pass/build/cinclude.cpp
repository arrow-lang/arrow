// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <string>

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

CXChildVisitResult cx_visit(
  CXCursor cursor, CXCursor parent, CXClientData clientData);

auto Build::handle_cinclude(ptr<ast::CInclude> x) -> ptr<ir::Value> {
  // Initialize clang
  auto cx = clang_createIndex(1, 1);
  auto buffer = std::string("#include <") + x->source + std::string(">");
  auto file = CXUnsavedFile{"main.c", buffer.c_str(), buffer.size()};
  auto tu = clang_parseTranslationUnit(cx, "main.c", nullptr, 0, &file, 1,
    CXTranslationUnit_DetailedPreprocessingRecord |
    CXTranslationUnit_SkipFunctionBodies);

  // Prepare ...
  std::vector<ptr<ast::Node>> result;

  // TODO: Prepare primitive C types now

  // Visit!
  clang_visitChildren(clang_getTranslationUnitCursor(tu),
    &Build::_cx_visit, &result);

  // Dispose: clang
  clang_disposeTranslationUnit(tu);
  clang_disposeIndex(cx);

  // Iterate through result nodes
  for (auto& node : result) {
    run(node);
  }

  // No result value (null statement)
  return nullptr;
}

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
};

static std::string _c_typename(std::vector<arrow::ptr<arrow::ast::Node>>* nodes, CXType c_type) {
  // Determine typename
  auto c_typename = clang_getCString(clang_getTypeSpelling(c_type));
  auto typename_ = _c_typenames[c_typename];
  if (typename_ == "") return "";

  // Add C basic type
  // FIXME: If this is not the first C import in the module,
  //        do not do this
  return typename_;
}

CXChildVisitResult Build::_cx_visit(
  CXCursor cursor, CXCursor parent, CXClientData clientData
) {
  auto result = reinterpret_cast<std::vector<ptr<ast::Node>>*>(clientData);
  auto c_kind = clang_getCursorKind(cursor);
  auto c_name = clang_getCString(clang_getCursorSpelling(cursor));

  CXFile file;
  unsigned int line;
  unsigned int column;
  unsigned int offset;

  CXSourceLocation loc = clang_getCursorLocation(cursor);
  clang_getFileLocation(loc, &file, &line, &column, &offset);

  auto filename = clang_getCString(clang_getFileName(file));
  auto fn = filename == NULL ? std::string("") : std::string(filename);

  auto span = Span(fn, Position{line, column}, Position{line, column});

  switch (c_kind) {
  case CXCursor_TypedefDecl: {
    auto c_type = clang_getCanonicalType(clang_getCursorType(cursor));
    auto typename_ = _c_typename(result, c_type);
    if (typename_ == "") break;

    // Make
    result->push_back(make<ast::TypeAlias>(
      span, c_name, make<ast::TypeName>(span, typename_)));
  } return CXChildVisit_Continue;

  // case CXCursor_FunctionDecl: {
  //   auto c_type = clang_getCursorType(cursor);
  //
  //   // Get result type
  //   auto c_result_t = clang_getResultType(c_type);
  //   c_result_t = clang_getCanonicalType(c_result_t);
  //
  //   // Make
  //   result->push_back(make<ast::ExternFunction>(span, c_name));
  // } break;

  default:
    break;
  }

  Log::get().warn("unhandled: {} ({})", c_name, c_kind);

  return CXChildVisit_Continue;
}
