// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_TYPE_DEDUCE_H
#define ARROW_TYPE_DEDUCE_H

#include <memory>
#include <string>

#include "arrow/pass.hpp"

namespace arrow {
namespace pass {

class TypeDeduce : public Pass {
 public:
  using Pass::Pass;

  ptr<ir::Type> run(ptr<ast::Node>);

 private:
  // ptr<ir::Type> visit_block(ptr<ast::Block>);
  // ptr<ir::Type> visit_indirect(ptr<ast::Indirect>);
  // ptr<ir::Type> visit_address_of(ptr<ast::AddressOf>);
  // ptr<ir::Type> visit_identity(ptr<ast::Identity>);
  // ptr<ir::Type> visit_negate(ptr<ast::Negate>);
  // ptr<ir::Type> visit_add(ptr<ast::Add>);
  // ptr<ir::Type> visit_sub(ptr<ast::Sub>);
  // ptr<ir::Type> visit_mul(ptr<ast::Mul>);
  // ptr<ir::Type> visit_div(ptr<ast::Div>);
  // ptr<ir::Type> visit_mod(ptr<ast::Mod>);
  // ptr<ir::Type> visit_assign(ptr<ast::Assign>);
  // ptr<ir::Type> visit_call(ptr<ast::Call>);
  // ptr<ir::Type> visit_argument(ptr<ast::Argument>);
  // ptr<ir::Type> visit_return(ptr<ast::Return>);
  // ptr<ir::Type> visit_bit_not(ptr<ast::BitNot>);
  // ptr<ir::Type> visit_bit_and(ptr<ast::BitAnd>);
  // ptr<ir::Type> visit_bit_or(ptr<ast::BitOr>);
  // ptr<ir::Type> visit_bit_xor(ptr<ast::BitXor>);
  // ptr<ir::Type> visit_not(ptr<ast::Not>);
  // ptr<ir::Type> visit_and(ptr<ast::And>);
  // ptr<ir::Type> visit_or(ptr<ast::Or>);
  // ptr<ir::Type> visit_eq(ptr<ast::EqualTo>);
  // ptr<ir::Type> visit_ne(ptr<ast::NotEqualTo>);
  // ptr<ir::Type> visit_lt(ptr<ast::LessThan>);
  // ptr<ir::Type> visit_le(ptr<ast::LessThanOrEqualTo>);
  // ptr<ir::Type> visit_gt(ptr<ast::GreaterThan>);
  // ptr<ir::Type> visit_ge(ptr<ast::GreaterThanOrEqualTo>);
  ptr<ir::Type> visit_id(ptr<ast::Identifier>);
  ptr<ir::Type> visit_bool(ptr<ast::Boolean>);
  ptr<ir::Type> visit_int(ptr<ast::Integer>);
  ptr<ir::Type> visit_real(ptr<ast::Real>);
  ptr<ir::Type> visit_str(ptr<ast::String>);
  ptr<ir::Type> visit_expression_statement(ptr<ast::ExpressionStatement>);
  // ptr<ir::Type> visit_conditional(ptr<ast::Conditional>);
  // ptr<ir::Type> visit_repeat(ptr<ast::Repeat>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_TYPE_DEDUCE_H
