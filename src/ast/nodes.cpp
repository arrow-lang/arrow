// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ast/nodes.hpp"

namespace ast = arrow::ast;

ast::Node::~Node() noexcept { }

ast::Statement::~Statement() noexcept { }
ast::Module::~Module() noexcept { }
ast::Variable::~Variable() noexcept { }

ast::Expression::~Expression() noexcept { }
ast::Integer::~Integer() noexcept { }
ast::Float::~Float() noexcept { }
ast::Boolean::~Boolean() noexcept { }
ast::String::~String() noexcept { }

ast::Type::~Type() noexcept { }
ast::TypeName::~TypeName() noexcept { }
