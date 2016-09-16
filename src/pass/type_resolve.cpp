// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::pass::TypeResolve;

TypeResolve::TypeResolve(GContext& ctx) : Pass(ctx), _types() {
  // Register built-in types
  // Boolean
  _types.emplace("bool", make<ir::TypeBoolean>());

  // Integer, Signed
  _types.emplace("int8", make<ir::TypeInteger>(true, 8));
  _types.emplace("int16", make<ir::TypeInteger>(true, 16));
  _types.emplace("int32", make<ir::TypeInteger>(true, 32));
  _types.emplace("int64", make<ir::TypeInteger>(true, 64));
  _types.emplace("int128", make<ir::TypeInteger>(true, 128));

  // Integer, Unsigned
  _types.emplace("uint8", make<ir::TypeInteger>(false, 8));
  _types.emplace("uint16", make<ir::TypeInteger>(false, 16));
  _types.emplace("uint32", make<ir::TypeInteger>(false, 32));
  _types.emplace("uint64", make<ir::TypeInteger>(false, 64));
  _types.emplace("uint128", make<ir::TypeInteger>(false, 128));

  // Real
  _types.emplace("float32", make<ir::TypeReal>(32));
  _types.emplace("float64", make<ir::TypeReal>(64));

  // String
  _types.emplace("str", make<ir::TypeString>());
}

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(node))

auto TypeResolve::run(ptr<ast::Type> node) -> ptr<ir::Type> {
  Match(*node) {
    ACCEPT(ast::TypeName, type_name);

    Otherwise() {
      Log::get().error("middle::TypeResolve not implemented for {}", typeid(*node).name());
    }
  } EndMatch;

  return nullptr;
}
