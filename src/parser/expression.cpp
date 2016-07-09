// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

static std::map<Token::Type, unsigned> UNARY = {
  // Identitiy, Negation, Bitwise NOT [2]
  {Token::Type::Plus,            2000},
  {Token::Type::Minus,           2000},
  {Token::Type::ExclamationMark, 2000},

  // Logical NOT [11]
  // TODO: Investigate this value and comment
  {Token::Type::Not,             1100},
};

// First part of the pair is the token power; second is the
// associativity (1 for left-to-right and 0 for right-to-left).
static std::map<Token::Type, std::pair<unsigned, unsigned>> BINARY = {
  // Multiplication, Division, Remainder [3]
  {Token::Type::Asterisk,                {1900,  1}},
  {Token::Type::Percent,                 {1900,  1}},
  {Token::Type::Slash,                   {1900,  1}},

  // Addition and subtraction [4]
  {Token::Type::Plus,                    {1800,  1}},
  {Token::Type::Minus,                   {1800,  1}},

  // Bitwise AND [5]
  {Token::Type::Ampersand,               {1700,  1}},

  // Bitwise XOR [6]
  {Token::Type::Caret,                   {1600,  1}},

  // Bitwise OR [7]
  {Token::Type::Pipe,                    {1500,  1}},

  // Greater than; and, greater than or equal to [8]
  {Token::Type::GreaterThan_Equals,      {1400,  1}},
  {Token::Type::GreaterThan,             {1400,  1}},

  // Less than; and, less than or equal to [8]
  {Token::Type::LessThan,                {1400,  1}},
  {Token::Type::LessThan_Equals,         {1400,  1}},

  // Equal to; and, not equal to [10]
  {Token::Type::Equals_Equals,           {1200,  1}},
  {Token::Type::ExclamationMark_Equals,  {1200,  1}},

  // do_logical AND [12]
  {Token::Type::And,                     {1000,  1}},

  // do_logical OR [13]
  {Token::Type::Or,                      { 900,  1}},

  // Assignment [15]
  {Token::Type::Equals,                  { 700, -1}},
  // {Token::Type::Plus_Equals,             { 700, -1}},
  // {Token::Type::Minus_Equals,            { 700, -1}},
  // {Token::Type::Asterisk_Equals,         { 700, -1}},
  // {Token::Type::Slash_Equals,            { 700, -1}},
  // {Token::Type::Percent_Equals,          { 700, -1}},
  // {Token::Type::Ampersand_Equals,        { 700, -1}},
  // {Token::Type::Caret_Equals,            { 700, -1}},
  // {Token::Type::Pipe_Equals,             { 700, -1}},
};

auto Parser::parse_primary_expression() -> ptr<ast::Expression> {
  switch (_t.peek()->type) {
  case token::Type::Integer:
    return parse_integer();

  case token::Type::True:
  case token::Type::False:
    return parse_bool();

  case token::Type::Float:
    return parse_float();

  case token::Type::String:
    return parse_str();

  case token::Type::Identifier:
    return parse_id();

  default:
    Log::get().error(_t.pop()->span, "expected expression");
    return nullptr;
  }
}

auto Parser::parse_expression() -> ptr<ast::Expression> {

}
