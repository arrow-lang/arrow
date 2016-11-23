// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_TYPE_RESOLVE_H
#define ARROW_TYPE_RESOLVE_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "arrow/pass.hpp"
#include "arrow/ast/visitor.hpp"

namespace arrow {
namespace pass {

class TypeResolve : public ast::Visitor, public Pass {
 public:
  using Pass::Pass;

  virtual void run(ptr<ast::Node>);
  void run_together(std::vector<ptr<ast::Node>>);

 private:
  struct Assign { ptr<ir::Type> type; };
  struct Use { ptr<ir::Type> type; };

  std::unordered_set<ptr<ir::Variable>> _declare;
  std::unordered_map<ir::Variable*, std::vector<Assign>> _assigns;
  std::unordered_map<ir::Variable*, std::vector<Use>> _uses;
  std::stack<ptr<ir::Type>> _type_s;
  bool _incomplete = false;

  void visit_module(ptr<ast::Module>);
  void visit_block(ptr<ast::Block>);
  void visit_variable(ptr<ast::Variable>);
  void visit_assign(ptr<ast::Assign>);
  void visit_function(ptr<ast::Function>);
  void visit_id(ptr<ast::Identifier>);
  void visit_call(ptr<ast::Call>);
  void visit_extern_function(ptr<ast::ExternFunction>);
  void visit_extern_variable(ptr<ast::ExternVariable>);
  void visit_unary(ptr<ast::Unary>);
  void visit_binary(ptr<ast::Binary>);
  void visit_address_of(ptr<ast::AddressOf>);
  void visit_indirect(ptr<ast::Indirect>);
  void visit_type_alias(ptr<ast::TypeAlias>);
  void visit_type_record(ptr<ast::TypeRecord>);
  void visit_implement(ptr<ast::Implement>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_TYPE_RESOLVE_H
