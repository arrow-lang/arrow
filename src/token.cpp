// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <string>

#include "arrow/token.hpp"

using arrow::token::Token;
using arrow::token::Integer;
using arrow::token::Float;

Token::Token(Type type, Span span) noexcept : type(type), span(span) {
}

Token::~Token() noexcept {
}

Integer::Integer(Span span, const std::string& text, unsigned base) :
  Token(Type::Integer, span), value(text, base) {
}

Integer::~Integer() noexcept {
}

Float::Float(Span span, long double value) :
  Token(Type::Float, span), value(value) {
}

Float::~Float() noexcept {
}

std::ostream& arrow::token::operator<<(
  std::ostream &os, const Type &type
) {
  switch (type) {
  case Type::End:     return os << "end";
  case Type::Integer: return os << "integer";
  case Type::Float:   return os << "float";
  }

  return os << "?";
}
