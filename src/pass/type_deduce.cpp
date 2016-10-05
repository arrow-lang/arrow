// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::pass::TypeDeduce;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return visit_##name(std::dynamic_pointer_cast<type>(x))

auto TypeDeduce::run(ptr<ast::Node> x) -> ptr<ir::Type> {
  Match(*x) {
    ACCEPT(ast::Identifier, id);
    ACCEPT(ast::Boolean, bool);
    ACCEPT(ast::Integer, int);
    ACCEPT(ast::String, str);
    ACCEPT(ast::Real, real);
    ACCEPT(ast::ExpressionStatement, expression_statement);
    // ACCEPT(ast::Indirect, indirect);
    // ACCEPT(ast::AddressOf, address_of);
    ACCEPT(ast::Identity, identity);
    ACCEPT(ast::Negate, negate);
    ACCEPT(ast::Add, add);
    ACCEPT(ast::Sub, sub);
    ACCEPT(ast::Mul, mul);
    ACCEPT(ast::Div, div);
    ACCEPT(ast::Mod, mod);
    ACCEPT(ast::Assign, assign);
    ACCEPT(ast::Call, call);
    ACCEPT(ast::BitNot, bit_not);
    ACCEPT(ast::BitAnd, bit_and);
    ACCEPT(ast::BitOr, bit_or);
    ACCEPT(ast::BitXor, bit_xor);
    ACCEPT(ast::Not, not);
    ACCEPT(ast::And, and);
    ACCEPT(ast::Or, or);
    ACCEPT(ast::EqualTo, eq);
    ACCEPT(ast::NotEqualTo, ne);
    ACCEPT(ast::LessThan, lt);
    ACCEPT(ast::LessThanOrEqualTo, le);
    ACCEPT(ast::GreaterThan, gt);
    ACCEPT(ast::GreaterThanOrEqualTo, ge);
    ACCEPT(ast::Block, block);
    ACCEPT(ast::Conditional, conditional);
    ACCEPT(ast::Branch, branch);
    ACCEPT(ast::Unit, unit);

    Otherwise() {
      // Unhandled
    }
  } EndMatch;

  return nullptr;
}
