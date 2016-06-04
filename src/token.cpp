// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <string>

#include "arrow/token.hpp"

using arrow::token::Token;
using arrow::token::Integer;

Token::Token(Type type, Span span) noexcept : type(type), span(span) {
}

Token::~Token() noexcept {
}

Integer::Integer(Span span, const std::string& text) :
  Token(Type::Integer, span), value(text) {
}

Integer::~Integer() noexcept {
}
