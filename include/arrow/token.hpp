// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_TOKEN_H
#define ARROW_TOKEN_H

#include <gmpxx.h>

#include <string>

#include "arrow/span.hpp"

namespace arrow {
namespace token {

enum class Type {
  End = 0,

  // Derivatives
  Symbol,
  Keyword,
  Identifier,
  Integer,
  Real,
  String,

  // Keywords
  And,
  Or,
  Not,
  Let,
  Mutable,
  Def,
  Extern,
  True,
  False,
  If,
  Unless,
  Else,
  Loop,
  While,
  Until,
  Break,
  Continue,
  Return,
  Global,
  As,
  Struct,
  Underscore,

  // Symbols: 1-character
  Plus,
  Minus,
  Slash,
  Asterisk,
  Percent,
  Ampersand,
  Pipe,
  Caret,
  ExclamationMark,
  Equals,
  LessThan,
  GreaterThan,
  Period,
  Colon,
  Semicolon,
  LeftBrace,
  RightBrace,
  LeftParenthesis,
  RightParenthesis,
  LeftBracket,
  RightBracket,
  Comma,

  // Symbols: 2-character
  Plus_Equals,
  Minus_Equals,
  Asterisk_Equals,
  Slash_Equals,
  Percent_Equals,
  Ampersand_Equals,
  Pipe_Equals,
  Caret_Equals,
  Equals_Equals,
  ExclamationMark_Equals,
  GreaterThan_Equals,
  LessThan_Equals,
};

extern std::ostream &operator<<(std::ostream &os, const Type &type);

struct Token {
  explicit Token(Type type, Span span) noexcept;

  virtual ~Token() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << type;
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
    return os << type << ": " << value.get_str(10);
  }

  // Normalized integer (arbitrary-precision)
  mpz_class value;
};

struct Real : Token {
  Real(Span span, long double value);

  virtual ~Real() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << type << ": " << value;
  }

  // Normalized float
  long double value;
};

struct Keyword : Token {
  Keyword(Type type, Span span);

  virtual ~Keyword() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << "keyword: " << type;
  }
};

struct Identifier : Token {
  Identifier(Span span, std::string text);

  virtual ~Identifier() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << type << ": " << text;
  }

  std::string text;
};

struct String : Token {
  String(Span span, std::string text);

  virtual ~String() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << type << ": " << text;
  }

  std::string text;
};

struct Symbol : Token {
  Symbol(Type type, Span span);

  virtual ~Symbol() noexcept;

  virtual std::ostream& print(std::ostream &os) const {
    return os << "symbol: " << type;
  }
};

}  // namespace token
}  // namespace arrow

namespace std {

template <> struct hash<arrow::token::Type> {
  std::size_t operator() (const arrow::token::Type& t) const noexcept {
    return std::size_t(t);
  }
};

}  // namespace std

#endif  // ARROW_TOKEN_H
