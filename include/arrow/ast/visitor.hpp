// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_VISITOR_H
#define ARROW_AST_VISITOR_H

#include "arrow/ast/nodes.hpp"

namespace arrow {
namespace ast {

class Visitor {
 public:
  Visitor();

  Visitor(const Visitor& other) = delete;
  Visitor(Visitor&& other) = delete;

  Visitor& operator=(const Visitor& other) = delete;
  Visitor& operator=(Visitor&& other) = delete;

  virtual ~Visitor() noexcept;

  virtual void run(ptr<Node> node);
  void accept(ptr<Node> node);

 private:
  virtual void visit_return(ptr<ast::Return> x);
  virtual void visit_variable(ptr<ast::Variable> x);
  virtual void visit_block(ptr<ast::Block> x);
  virtual void visit_branch(ptr<ast::Branch> x);
  virtual void visit_conditional(ptr<ast::Conditional> x);
  virtual void visit_repeat(ptr<ast::Repeat> x);
  virtual void visit_call(ptr<ast::Call> x);
  virtual void visit_argument(ptr<ast::Argument> x);
  virtual void visit_identity(ptr<ast::Identity> x);
  virtual void visit_negate(ptr<ast::Negate> x);
  virtual void visit_bit_not(ptr<ast::BitNot> x);
  virtual void visit_not(ptr<ast::Not> x);
  virtual void visit_indirect(ptr<ast::Indirect> x);
  virtual void visit_address_of(ptr<ast::AddressOf> x);
  virtual void visit_mul(ptr<ast::Mul> x);
  virtual void visit_div(ptr<ast::Div> x);
  virtual void visit_mod(ptr<ast::Mod> x);
  virtual void visit_add(ptr<ast::Add> x);
  virtual void visit_sub(ptr<ast::Sub> x);
  virtual void visit_bit_and(ptr<ast::BitAnd> x);
  virtual void visit_bit_xor(ptr<ast::BitXor> x);
  virtual void visit_bit_or(ptr<ast::BitOr> x);
  virtual void visit_gte(ptr<ast::GreaterThanOrEqualTo> x);
  virtual void visit_gt(ptr<ast::GreaterThan> x);
  virtual void visit_lt(ptr<ast::LessThan> x);
  virtual void visit_lte(ptr<ast::LessThanOrEqualTo> x);
  virtual void visit_eq(ptr<ast::EqualTo> x);
  virtual void visit_ne(ptr<ast::NotEqualTo> x);
  virtual void visit_and(ptr<ast::And> x);
  virtual void visit_or(ptr<ast::Or> x);
  virtual void visit_assign(ptr<ast::Assign> x);
  virtual void visit_expression_statement(ptr<ast::ExpressionStatement> x);

  virtual void visit_unary(ptr<ast::Unary> x);
  virtual void visit_binary(ptr<ast::Binary> x);

  virtual void visit_module(ptr<ast::Module> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_integer(ptr<ast::Integer> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_bool(ptr<ast::Boolean> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_str(ptr<ast::String> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_real(ptr<ast::Real> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_id(ptr<ast::Identifier> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_type_name(ptr<ast::TypeName> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_type_pointer(ptr<ast::TypePointer> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_type_alias(ptr<ast::TypeAlias> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_function(ptr<ast::Function> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_extern_function(ptr<ast::ExternFunction> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_parameter(ptr<ast::Parameter> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_import(ptr<ast::Import> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_cinclude(ptr<ast::CInclude> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_break(ptr<ast::Break> x) { /* LCOV_EXCL_LINE */ }
  virtual void visit_continue(ptr<ast::Continue> x) { /* LCOV_EXCL_LINE */ }
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_VISITOR_H
