// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <unordered_map>
#include <vector>
#include <utility>

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;
namespace token = arrow::token;

template <typename TKey, typename TValue>
static std::vector<TKey> keys_of(std::unordered_map<TKey, TValue> map) {
  std::vector<TKey> result;
  result.reserve(map.size());

  for (auto const& item : map) {
    result.push_back(item.first);
  }

  return result;
}

static std::unordered_map<token::Type, unsigned> UNARY = {
  // Identitiy, Negation, Bitwise NOT, Address Of, Indirect [2]
  {token::Type::Plus,            2000},
  {token::Type::Minus,           2000},
  {token::Type::Tilde,           2000},
  {token::Type::Ampersand,       2000},
  {token::Type::Asterisk,        2000},

  // Logical NOT [11]
  {token::Type::Not,             1100},
};

// First part of the pair is the token power; second is the
// associativity (1 for left-to-right and 0 for right-to-left).
static std::unordered_map<token::Type, std::pair<unsigned, unsigned>> BINARY = {
  // Multiplication, Division, Remainder [3]
  {token::Type::Asterisk,                {1900,  1}},
  {token::Type::Percent,                 {1900,  1}},
  {token::Type::Slash,                   {1900,  1}},

  // Addition and subtraction [4]
  {token::Type::Plus,                    {1800,  1}},
  {token::Type::Minus,                   {1800,  1}},

  // Bitwise AND [5]
  {token::Type::Ampersand,               {1700,  1}},

  // Bitwise XOR [6]
  {token::Type::Caret,                   {1600,  1}},

  // Bitwise OR [7]
  {token::Type::Pipe,                    {1500,  1}},

  // Greater than; and, greater than or equal to [8]
  {token::Type::GreaterThan_Equals,      {1400,  1}},
  {token::Type::GreaterThan,             {1400,  1}},

  // Less than; and, less than or equal to [8]
  {token::Type::LessThan,                {1400,  1}},
  {token::Type::LessThan_Equals,         {1400,  1}},

  // Equal to; and, not equal to [10]
  {token::Type::Equals_Equals,           {1200,  1}},
  {token::Type::ExclamationMark_Equals,  {1200,  1}},

  // do_logical AND [12]
  {token::Type::And,                     {1000,  1}},

  // do_logical OR [13]
  {token::Type::Or,                      { 900,  1}},

  // Assignment [15]
  {token::Type::Equals,                  { 700, -1}},
  // {token::Type::Plus_Equals,             { 700, -1}},
  // {token::Type::Minus_Equals,            { 700, -1}},
  // {token::Type::Asterisk_Equals,         { 700, -1}},
  // {token::Type::Slash_Equals,            { 700, -1}},
  // {token::Type::Percent_Equals,          { 700, -1}},
  // {token::Type::Ampersand_Equals,        { 700, -1}},
  // {token::Type::Caret_Equals,            { 700, -1}},
  // {token::Type::Pipe_Equals,             { 700, -1}},
};

auto Parser::parse_expression(unsigned power/* = 0*/) -> ptr<ast::Expression> {
  ptr<ast::Expression> operand = nullptr;

  for (;;) {
    auto tok = _t.peek();
    if (tok->type == token::Type::End) break;

    // Match unary expression to LHS unless we have a previously matched LHS
    if (!operand) {
      auto u = UNARY.find(tok->type);
      if (u != UNARY.end()) {
        operand = parse_unary_expression();
        if (!operand) return nullptr;
        continue;
      }
    }

    // Match binary expression if we previously matched a LHS
    if (operand) {
      auto b = BINARY.find(tok->type);
      if (b != BINARY.end()) {
        int result = 0;
        auto tmp = parse_binary_expression(operand, power, &result);

        // Keep going; we got a valid binary expression
        if (tmp && result == 1) { operand = tmp; continue; }
        // Ordering rules say we shouldn't combine
        else if (result == -1) break;
        // We did not get a valid operand
        else if (!operand) return nullptr;
      } else {
        // Couldn't match
        break;
      }
    }

    // Match postfix (fallsback to primary) expression
    operand = parse_postfix_expression();
    if (!operand) return nullptr;
  }

  if (!operand) {
    auto tok = _t.pop();
    Log::get().error(tok->span, "expected expression; found {}", tok->type);

    return nullptr;
  }

  return operand;
}

auto Parser::parse_unary_expression() -> ptr<ast::Expression> {
  // Expect a unary token
  std::vector<token::Type> tokens = keys_of(UNARY);
  auto tok = expect(tokens);
  if (!tok) return nullptr;

  // Get unary token 'power'
  auto tok_power = UNARY[tok->type];

  // Expect an expression
  auto operand = parse_expression(tok_power + 1);
  if (!operand) return nullptr;

  // Construct the unary expression node
  auto sp = tok->span.extend(operand->span);
  ptr<ast::Expression> result;
  switch (tok->type) {
    case token::Type::Plus:
      result = make<ast::Identity>(sp, operand);
      break;

    case token::Type::Minus:
      result = make<ast::Negate>(sp, operand);
      break;

    case token::Type::Tilde:
      result = make<ast::BitNot>(sp, operand);
      break;

    case token::Type::Not:
      result = make<ast::Not>(sp, operand);
      break;

    case token::Type::Asterisk:
      result = make<ast::Indirect>(sp, operand);
      break;

    case token::Type::Ampersand:
      result = make<ast::AddressOf>(sp, operand);
      break;

    default:
      // unreachable
      break;
  }

  return result;
}

auto Parser::parse_binary_expression(
  ptr<ast::Expression> lhs, unsigned power, int* rv
) -> ptr<ast::Expression> {
  // Expect a binary token
  std::vector<token::Type> tokens = keys_of(BINARY);
  auto tok = expect(tokens, false);
  if (!tok) return nullptr;

  // Get binary token 'power' and 'associativity'
  auto tok_ref = BINARY[tok->type];
  auto tok_power = tok_ref.first;
  auto tok_assoc = tok_ref.second;

  // Check if we should consume this token
  if (tok_power < power) return *rv = -1, nullptr;
  _t.pop();

  // Parse the RHS
  auto rhs = parse_expression(tok_power + tok_assoc);
  if (!rhs) return nullptr;

  // Construct the binary expression node
  auto sp = tok->span.extend(lhs->span);
  ptr<ast::Expression> result;
  switch (tok->type) {
    case token::Type::Asterisk:
      result = make<ast::Mul>(sp, lhs, rhs);
      break;

    case token::Type::Percent:
      result = make<ast::Mod>(sp, lhs, rhs);
      break;

    case token::Type::Slash:
      result = make<ast::Div>(sp, lhs, rhs);
      break;

    case token::Type::Plus:
      result = make<ast::Add>(sp, lhs, rhs);
      break;

    case token::Type::Minus:
      result = make<ast::Sub>(sp, lhs, rhs);
      break;

    case token::Type::Ampersand:
      result = make<ast::BitAnd>(sp, lhs, rhs);
      break;

    case token::Type::Caret:
      result = make<ast::BitXor>(sp, lhs, rhs);
      break;

    case token::Type::Pipe:
      result = make<ast::BitOr>(sp, lhs, rhs);
      break;

    case token::Type::GreaterThan_Equals:
      result = make<ast::GreaterThanOrEqualTo>(sp, lhs, rhs);
      break;

    case token::Type::GreaterThan:
      result = make<ast::GreaterThan>(sp, lhs, rhs);
      break;

    case token::Type::LessThan:
      result = make<ast::LessThan>(sp, lhs, rhs);
      break;

    case token::Type::LessThan_Equals:
      result = make<ast::LessThanOrEqualTo>(sp, lhs, rhs);
      break;

    case token::Type::Equals_Equals:
      result = make<ast::EqualTo>(sp, lhs, rhs);
      break;

    case token::Type::ExclamationMark_Equals:
      result = make<ast::NotEqualTo>(sp, lhs, rhs);
      break;

    case token::Type::And:
      result = make<ast::And>(sp, lhs, rhs);
      break;

    case token::Type::Or:
      result = make<ast::Or>(sp, lhs, rhs);
      break;

    case token::Type::Equals:
      result = make<ast::Assign>(sp, lhs, rhs);
      break;

    default:
      // unreachable
      break;
  }

  return *rv = 1, result;
}

auto Parser::parse_postfix_expression() -> ptr<ast::Expression> {
  // Parse operand
  ptr<ast::Expression> op = parse_primary_expression();
  if (!op) return nullptr;

  for (;;) {
    // Check for a postfix start token
    auto tok = _t.peek();
    if (tok->type == token::Type::LeftParenthesis) {
      op = parse_call(op);
      if (!op) return nullptr;

      continue;
    }

    break;
  }

  return op;
}

auto Parser::parse_primary_expression() -> ptr<ast::Expression> {
  switch (_t.peek()->type) {
  case token::Type::Integer:
    return parse_integer();

  case token::Type::True:
  case token::Type::False:
    return parse_bool();

  case token::Type::Real:
    return parse_real();

  case token::Type::String:
    return parse_str();

  case token::Type::Identifier:
    return parse_id();

  case token::Type::If:
    return parse_conditional();

  case token::Type::LeftParenthesis: {
    // Pop the left parenthesis
    _t.pop();

    // Parse nested expression
    auto expr = parse_expression();
    if (!expr) return nullptr;

    // Expect the right parenthesis
    if (!expect(token::Type::RightParenthesis)) return nullptr;

    return expr;
  } break;

  default:
    auto tok = _t.pop();
    Log::get().error(tok->span, "expected expression; found {}", tok->type);

    return nullptr;
  }
}
