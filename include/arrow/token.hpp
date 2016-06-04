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
  Float,
};

extern std::ostream &operator<<(std::ostream &os, const Type &type);

struct Token {
  explicit Token(Type type, Span span) noexcept;

  virtual ~Token() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << "?";
  }

  friend std::ostream &operator<<(std::ostream &os, const Token &tok) {
    return tok.print(os);
  }

  // Type identifier for token
  Type type;

  // Location in source: filename, [begin, end)
  Span span;
};

struct Integer : Token {
  Integer(Span span, const std::string& text, unsigned base);

  virtual ~Integer() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << value.get_str(10);
  }

  // Normalized integer (arbitrary-precision)
  mpz_class value;
};

struct Float : Token {
  Float(Span span, long double value);

  virtual ~Float() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << value;
  }

  // Normalized integer (arbitrary-precision)
  long double value;
};

}  // namespace token
}  // namespace arrow
