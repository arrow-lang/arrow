// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_TYPE_BUILD_H
#define ARROW_TYPE_BUILD_H

#include <memory>
#include <string>
#include <unordered_map>

#include "arrow/pass.hpp"

namespace arrow {
namespace pass {

class TypeBuild : public Pass {
 public:
  TypeBuild(GContext& ctx);

  ptr<ir::Type> run(ptr<ast::Node>);

 private:
  ptr<ir::Type> handle_type_name(ptr<ast::TypeName>);
  ptr<ir::Type> handle_id(ptr<ast::Identifier>);
  ptr<ir::TypePointer> handle_type_pointer(ptr<ast::TypePointer>);
  ptr<ir::Type> handle_type_unit(ptr<ast::TypeUnit>);
  ptr<ir::TypeFunction> handle_type_function(ptr<ast::TypeFunction>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_TYPE_BUILD_H
