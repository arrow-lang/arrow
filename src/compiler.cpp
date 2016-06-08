// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/compiler.hpp"
#include "arrow/log.hpp"
#include "arrow/ast.hpp"
#include "arrow/generator.hpp"

using arrow::Compiler;

Compiler::Compiler() : _btypes() {
  // Add basic types
  _btypes.emplace("bool", make<ir::TypeBoolean>());

  _btypes.emplace("int8", make<ir::TypeInteger>(true, 8));
  _btypes.emplace("int16", make<ir::TypeInteger>(true, 16));
  _btypes.emplace("int32", make<ir::TypeInteger>(true, 32));
  _btypes.emplace("int64", make<ir::TypeInteger>(true, 64));
  _btypes.emplace("int128", make<ir::TypeInteger>(true, 128));

  _btypes.emplace("uint8", make<ir::TypeInteger>(false, 8));
  _btypes.emplace("uint16", make<ir::TypeInteger>(false, 16));
  _btypes.emplace("uint32", make<ir::TypeInteger>(false, 32));
  _btypes.emplace("uint64", make<ir::TypeInteger>(false, 64));
  _btypes.emplace("uint128", make<ir::TypeInteger>(false, 128));
}

Compiler::~Compiler() noexcept {
}

void Compiler::compile(ptr<ast::Module> node) {
  // HACK: This is stupid and must be done better
  //       This is just a POC

  // Declare the top-level module
  auto module = make<ir::Module>(node->name);

  // Iterate through each statement
  for (auto& statement : node->statements) {
    Match(*statement) {
      Case(mch::C<ast::Variable>()) {
        auto item = cast<ast::Variable>(statement);

        auto type = make_type(item->type);
        if (!type) break;

        module->items.emplace(item->name, make<ir::Variable>(item->name, type));
      } break;
    } EndMatch;
  }

  // Generator: Convert IR into CODE (LLVM IR)
  Generator{}.run(module).print();
}

auto Compiler::make_type(ptr<ast::Type> node) -> ptr<ir::Type> {
  Match(*node) {
    Case(mch::C<ast::TypeName>()) {
      auto type_name = cast<ast::TypeName>(node);

      auto iter = _btypes.find(type_name->name);
      if (iter == _btypes.end()) {
        // No type found
        Log::get().error(node->span, "!");
        return nullptr;
      }

      return iter->second;
    } break;
  } EndMatch;

  // Not possible to get here
  return nullptr;
}
