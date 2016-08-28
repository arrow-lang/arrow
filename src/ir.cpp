// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"

namespace ir = arrow::ir;

ir::Node::~Node() noexcept { }
ir::Item::~Item() noexcept { }
ir::Module::~Module() noexcept { }
ir::Variable::~Variable() noexcept { }

ir::Type::~Type() noexcept { }
ir::TypeInteger::~TypeInteger() noexcept { }
ir::TypeBoolean::~TypeBoolean() noexcept { }

ir::Value::~Value() noexcept { }
ir::Integer::~Integer() noexcept { }
ir::Boolean::~Boolean() noexcept { }

ir::Binary::~Binary() noexcept {}
ir::Add::~Add() noexcept {}
ir::Assign::~Assign() noexcept {}
