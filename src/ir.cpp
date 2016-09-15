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
