// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ast.hpp"

namespace ast = arrow::ast;

ast::Node::~Node() noexcept { }
ast::Module::~Module() noexcept { }
ast::Statement::~Statement() noexcept { }
ast::Variable::~Variable() noexcept { }
