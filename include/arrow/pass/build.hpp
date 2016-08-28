// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_BUILD_H
#define ARROW_BUILD_H

#include <memory>
#include <string>

#include "arrow/pass.hpp"

namespace arrow {
namespace pass {

class Build : public Pass {
 public:
  using Pass::Pass;

  ptr<ir::Value> run(ptr<ast::Node>);

 private:
  ptr<ir::Value> handle_module(ptr<ast::Module>);
  ptr<ir::Value> handle_variable(ptr<ast::Variable>);
  ptr<ir::Value> handle_assign(ptr<ast::Assign>);
  ptr<ir::Value> handle_id(ptr<ast::Identifier>);
  ptr<ir::Value> handle_bool(ptr<ast::Boolean>);
  ptr<ir::Value> handle_int(ptr<ast::Integer>);
  ptr<ir::Value> handle_expression_statement(ptr<ast::ExpressionStatement>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_BUILD_H
