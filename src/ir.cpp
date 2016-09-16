// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"

namespace ir = arrow::ir;

ir::Node::~Node() noexcept { }
ir::Item::~Item() noexcept { }
ir::Module::~Module() noexcept { }
ir::Variable::~Variable() noexcept { }
ir::Function::~Function() noexcept { }

ir::Type::~Type() noexcept { }
ir::TypeInteger::~TypeInteger() noexcept { }
ir::TypeBoolean::~TypeBoolean() noexcept { }
ir::TypeReal::~TypeReal() noexcept { }
ir::TypeLiteralInteger::~TypeLiteralInteger() noexcept { }
ir::TypeLiteralReal::~TypeLiteralReal() noexcept { }
ir::TypeFunction::~TypeFunction() noexcept { }

ir::Value::~Value() noexcept { }
ir::Transmute::~Transmute() noexcept { }
ir::Integer::~Integer() noexcept { }
ir::Real::~Real() noexcept { }
ir::Boolean::~Boolean() noexcept { }

ir::Unary::~Unary() noexcept {}
ir::Negate::~Negate() noexcept {}

ir::Binary::~Binary() noexcept {}
ir::Add::~Add() noexcept {}
ir::Sub::~Sub() noexcept {}
ir::Mul::~Mul() noexcept {}
ir::Div::~Div() noexcept {}
ir::Mod::~Mod() noexcept {}
ir::Assign::~Assign() noexcept {}
ir::Call::~Call() noexcept {}
ir::Return::~Return() noexcept {}

ir::BitNot::~BitNot() noexcept {}
ir::BitAnd::~BitAnd() noexcept {}
ir::BitOr::~BitOr() noexcept {}
ir::BitXor::~BitXor() noexcept {}

ir::Not::~Not() noexcept {}
ir::And::~And() noexcept {}
ir::Or::~Or() noexcept {}

ir::EqualTo::~EqualTo() noexcept {}
ir::NotEqualTo::~NotEqualTo() noexcept {}
ir::LessThan::~LessThan() noexcept {}
ir::LessThanOrEqualTo::~LessThanOrEqualTo() noexcept {}
ir::GreaterThan::~GreaterThan() noexcept {}
ir::GreaterThanOrEqualTo::~GreaterThanOrEqualTo() noexcept {}

// Reduce 2 types following simple rules
arrow::ptr<ir::Type> arrow::ir::type_reduce(ptr<ir::Type> a, ptr<ir::Type> b) {
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
bool arrow::ir::type_is_assignable(ptr<ir::Type> lhs, ptr<ir::Type> rhs) {
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
