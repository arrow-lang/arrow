// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#pragma once

#include <gmpxx.h>

#include <string>

#include "arrow/span.hpp"

namespace arrow {
namespace token {

enum class Type {
  End = 0,
  Integer,
};

struct Token {
  explicit Token(Type type, Span span) noexcept;

  virtual ~Token() noexcept;

  // Type identifier for token
  Type type;

  // Location in source: filename, [begin, end)
  Span span;
};

struct Integer : Token {
  Integer(Span span, const std::string& text);

  virtual ~Integer() noexcept;

  // Normalized integer (arbitrary-precision)
  mpz_class value;
};

}  // namespace token
}  // namespace arrow
