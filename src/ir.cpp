// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"

namespace ir = arrow::ir;

ir::Item::~Item() noexcept { }
ir::Module::~Module() noexcept { }
ir::Type::~Type() noexcept { }
ir::TypeInteger::~TypeInteger() noexcept { }
ir::TypeBoolean::~TypeBoolean() noexcept { }
ir::Variable::~Variable() noexcept { }
