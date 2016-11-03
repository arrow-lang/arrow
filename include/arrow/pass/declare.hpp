// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_DECLARE_H
#define ARROW_DECLARE_H

#include <memory>
#include <string>

#include "arrow/pass.hpp"
#include "arrow/ast/visitor.hpp"

namespace arrow {
namespace pass {

class Declare : public Pass, public ast::Visitor {
 public:
  using Pass::Pass;

 private:
  void visit_module(ptr<ast::Module>);
  void visit_block(ptr<ast::Block>);
  void visit_variable(ptr<ast::Variable>);
  void visit_type_alias(ptr<ast::TypeAlias>);
  void visit_function(ptr<ast::Function>);
  void visit_extern_function(ptr<ast::ExternFunction>);
  void visit_cinclude(ptr<ast::CInclude>);
  void visit_extern_variable(ptr<ast::ExternVariable>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_DECLARE_H
