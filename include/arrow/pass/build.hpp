// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_BUILD_H
#define ARROW_BUILD_H

#include <memory>
#include <string>
#include <stack>
#include <functional>

#include "arrow/pass.hpp"
#include "arrow/context.hpp"

namespace arrow {
namespace pass {

class Build : public Pass {
 public:
  using Pass::Pass;

  ptr<ir::Value> run(ptr<ast::Node>);

 private:
  ptr<ir::Value> handle_module(ptr<ast::Module>);
  ptr<ir::Block> handle_block(ptr<ast::Block>);
  ptr<ir::Value> handle_variable(ptr<ast::Variable>);
  ptr<ir::Value> handle_function(ptr<ast::Function>);
  ptr<ir::Value> handle_extern_function(ptr<ast::ExternFunction>);
  ptr<ir::Value> handle_extern_variable(ptr<ast::ExternVariable>);

  ptr<ir::Value> handle_indirect(ptr<ast::Indirect>);
  ptr<ir::Value> handle_address_of(ptr<ast::AddressOf>);

  ptr<ir::Value> handle_identity(ptr<ast::Identity>);
  ptr<ir::Value> handle_negate(ptr<ast::Negate>);

  ptr<ir::Value> handle_add(ptr<ast::Add>);
  ptr<ir::Value> handle_sub(ptr<ast::Sub>);
  ptr<ir::Value> handle_mul(ptr<ast::Mul>);
  ptr<ir::Value> handle_div(ptr<ast::Div>);
  ptr<ir::Value> handle_mod(ptr<ast::Mod>);
  ptr<ir::Value> handle_assign(ptr<ast::Assign>);
  ptr<ir::Value> handle_assign_add(ptr<ast::AssignAdd>);
  ptr<ir::Value> handle_assign_sub(ptr<ast::AssignSub>);
  ptr<ir::Value> handle_assign_mul(ptr<ast::AssignMul>);
  ptr<ir::Value> handle_assign_div(ptr<ast::AssignDiv>);
  ptr<ir::Value> handle_assign_mod(ptr<ast::AssignMod>);
  ptr<ir::Value> handle_assign_bit_and(ptr<ast::AssignBitAnd>);
  ptr<ir::Value> handle_assign_bit_or(ptr<ast::AssignBitOr>);
  ptr<ir::Value> handle_assign_bit_xor(ptr<ast::AssignBitXor>);
  ptr<ir::Value> handle_call(ptr<ast::Call>);
  ptr<ir::Value> handle_argument(ptr<ast::Argument>);
  ptr<ir::Value> handle_return(ptr<ast::Return>);

  ptr<ir::Value> handle_bit_not(ptr<ast::BitNot>);
  ptr<ir::Value> handle_bit_and(ptr<ast::BitAnd>);
  ptr<ir::Value> handle_bit_or(ptr<ast::BitOr>);
  ptr<ir::Value> handle_bit_xor(ptr<ast::BitXor>);
  ptr<ir::Value> handle_bit_left_shift(ptr<ast::BitLeftShift>);
  ptr<ir::Value> handle_bit_right_shift(ptr<ast::BitRightShift>);

  ptr<ir::Value> handle_not(ptr<ast::Not>);
  ptr<ir::Value> handle_and(ptr<ast::And>);
  ptr<ir::Value> handle_or(ptr<ast::Or>);

  ptr<ir::Value> handle_eq(ptr<ast::EqualTo>);
  ptr<ir::Value> handle_ne(ptr<ast::NotEqualTo>);
  ptr<ir::Value> handle_lt(ptr<ast::LessThan>);
  ptr<ir::Value> handle_le(ptr<ast::LessThanOrEqualTo>);
  ptr<ir::Value> handle_gt(ptr<ast::GreaterThan>);
  ptr<ir::Value> handle_ge(ptr<ast::GreaterThanOrEqualTo>);

  ptr<ir::Value> handle_id(ptr<ast::Identifier>);
  ptr<ir::Value> handle_name(ptr<ast::Name>);
  ptr<ir::Value> handle_path(ptr<ast::Path>);
  ptr<ir::Value> handle_bool(ptr<ast::Boolean>);
  ptr<ir::Value> handle_int(ptr<ast::Integer>);
  ptr<ir::Value> handle_real(ptr<ast::Real>);
  ptr<ir::Value> handle_str(ptr<ast::String>);
  ptr<ir::Value> handle_unit(ptr<ast::Unit>);

  ptr<ir::Value> handle_expression_statement(ptr<ast::ExpressionStatement>);

  ptr<ir::Value> handle_import(ptr<ast::Import>);
  ptr<ir::Value> handle_type_alias(ptr<ast::TypeAlias>);

  ptr<ir::Value> handle_cinclude(ptr<ast::CInclude>);

  ptr<ir::Value> handle_conditional(ptr<ast::Conditional>);
  ptr<ir::Value> handle_repeat(ptr<ast::Repeat>);
  ptr<ir::Value> handle_break(ptr<ast::Break>);
  ptr<ir::Value> handle_continue(ptr<ast::Continue>);

  ptr<ir::Value> handle_transmute(ptr<ast::Transmute>);

  ptr<ir::Value> _assign(
    ptr<ast::Binary> x,
    std::function<ptr<ir::Type>(ptr<ir::Value>, ptr<ir::Value>)> deduce,
    std::function<ptr<ir::Value>(ptr<ir::Type>, ptr<ir::Value>, ptr<ir::Value>)> make
  );

  Context<bool> _expression_c;
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_BUILD_H
