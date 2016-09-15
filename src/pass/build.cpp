// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::pass::Build;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(x))

auto Build::run(ptr<ast::Node> x) -> ptr<ir::Value> {
  Match(*x) {
    ACCEPT(ast::Module, module);
    ACCEPT(ast::Variable, variable);
    ACCEPT(ast::Function, function);

    ACCEPT(ast::Identifier, id);
    ACCEPT(ast::Boolean, bool);
    ACCEPT(ast::Integer, int);
    ACCEPT(ast::Real, real);
    ACCEPT(ast::ExpressionStatement, expression_statement);

    ACCEPT(ast::Identity, identity);
    ACCEPT(ast::Negate, negate);

    ACCEPT(ast::Add, add);
    ACCEPT(ast::Sub, sub);
    ACCEPT(ast::Mul, mul);
    ACCEPT(ast::Div, div);
    ACCEPT(ast::Mod, mod);
    ACCEPT(ast::Assign, assign);
    ACCEPT(ast::Call, call);
    ACCEPT(ast::Argument, argument);
    ACCEPT(ast::Return, return);

    ACCEPT(ast::BitNot, bit_not);
    ACCEPT(ast::BitAnd, bit_and);
    ACCEPT(ast::BitOr, bit_or);
    ACCEPT(ast::BitXor, bit_xor);

    ACCEPT(ast::Not, not);
    ACCEPT(ast::And, and);
    ACCEPT(ast::Or, or);

    Otherwise() {
      Log::get().error("build not implemented for {}", typeid(*x).name());
    }
  } EndMatch;

  return nullptr;
}

// Reduce 2 types following simple rules
auto Build::_type_reduce(ptr<ir::Type> a, ptr<ir::Type> b) -> ptr<ir::Type> {
  // Same type
  if (a->is_equal(b)) return a;

  // Integer + Integer OR Real + Real
  if (
    (a->is_real() && b->is_real()) ||
    (a->is_integer() && b->is_integer())
  ) {
    // Handle is_equal
    if (a->is_equal(b)) return a;

    // Handle a (Literal) on either side; the type should go
    // to the other side
    if (a->size() == 0 && b->size() > 0) {
      return b;
    }

    if (b->size() == 0 && a->size() > 0) {
      return a;
    }
  }

  // Real + Literal Integer
  if (
    a->is_real() && b->is_integer() &&
    b->size() == 0
  ) {
    return a;
  }

  // Literal Integer + Real
  if (
    b->is_real() && a->is_integer() &&
    a->size() == 0
  ) {
    return b;
  }

  return nullptr;
}

// Check if type RHS is assignable to type LHS
bool Build::_type_is_assignable(ptr<ir::Type> lhs, ptr<ir::Type> rhs) const {
  return (
    // Equal
    (lhs->is_equal(rhs)) ||
    // Integer & Literal Integer
    (
      lhs->is_integer() && rhs->is_integer() &&
      (lhs->size() == 0 || rhs->size() == 0)
    ) ||
    // Real & Literal Real
    (
      lhs->is_real() && rhs->is_real() &&
      (lhs->size() == 0 || rhs->size() == 0)
    ) ||
    // Real & Literal Integer
    (lhs->is_real() && rhs->is_integer() && rhs->size() == 0)
  );
}
