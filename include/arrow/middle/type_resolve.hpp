// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_MIDDLE_TYPE_RESOLVE_H
#define ARROW_MIDDLE_TYPE_RESOLVE_H

#include <string>
#include <unordered_map>

#include "arrow/middle/pass.hpp"

namespace arrow {
namespace middle {

class TypeResolve : public Pass {
 public:
  explicit TypeResolve(Compiler::Context& ctx);

  ptr<ir::Type> run(ptr<ast::Type>);

 private:
  ptr<ir::Type> handle_type_name(ptr<ast::TypeName>);

  // Built-in types
  std::unordered_map<std::string, ptr<ir::Type>> _types;
};

}  // namespace middle
}  // namespace arrow

#endif  // ARROW_MIDDLE_TYPE_RESOLVE_H
