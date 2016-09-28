// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "fmt.hpp"

#include "arrow/ast/visitor.hpp"
#include "arrow/log.hpp"

using arrow::ast::Visitor;

Visitor::Visitor() {
}

Visitor::~Visitor() noexcept {
}

void Visitor::run(ptr<Node> node) {
  // NOTE: This method is intended as a point of extension
  accept(node);
}

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    visit_##name(std::dynamic_pointer_cast<type>(node)); break

void Visitor::accept(ptr<ast::Node> node) {
  Match(*node) {
    ACCEPT(Module, module);
    ACCEPT(Block, block);
    ACCEPT(Variable, variable);
    ACCEPT(ExpressionStatement, expression_statement);
    ACCEPT(Return, return);
    ACCEPT(Integer, integer);
    ACCEPT(Boolean, bool);
    ACCEPT(String, str);
    ACCEPT(Real, real);
    ACCEPT(Identifier, id);
    ACCEPT(Identity, identity);
    ACCEPT(Negate, negate);
    ACCEPT(BitNot, bit_not);
    ACCEPT(Not, not);
    ACCEPT(Indirect, indirect);
    ACCEPT(AddressOf, address_of);
    ACCEPT(Mul, mul);
    ACCEPT(Div, div);
    ACCEPT(Mod, mod);
    ACCEPT(Add, add);
    ACCEPT(Sub, sub);
    ACCEPT(BitAnd, bit_and);
    ACCEPT(BitXor, bit_xor);
    ACCEPT(BitOr, bit_or);
    ACCEPT(GreaterThanOrEqualTo, gte);
    ACCEPT(GreaterThan, gt);
    ACCEPT(LessThan, lt);
    ACCEPT(LessThanOrEqualTo, lte);
    ACCEPT(EqualTo, eq);
    ACCEPT(NotEqualTo, ne);
    ACCEPT(And, and);
    ACCEPT(Or, or);
    ACCEPT(Assign, assign);
    ACCEPT(TypeName, type_name);
    ACCEPT(TypePointer, type_pointer);
    ACCEPT(TypeAlias, type_alias);
    ACCEPT(Function, function);
    ACCEPT(ExternFunction, extern_function);
    ACCEPT(Parameter, parameter);
    ACCEPT(Call, call);
    ACCEPT(Argument, argument);
    ACCEPT(Import, import);
    ACCEPT(CInclude, cinclude);
    ACCEPT(Branch, branch);
    ACCEPT(Conditional, conditional);
    ACCEPT(Repeat, repeat);
    ACCEPT(Break, break);
    ACCEPT(Continue, continue);

    Otherwise() {
      Log::get().error("visitor not implemented for node: {}",
        typeid(*node).name());
    }
  } EndMatch
}

// Statement
void Visitor::visit_expression_statement(ptr<ast::ExpressionStatement> x) {
  accept(x->expression);
}

// Block
void Visitor::visit_block(ptr<ast::Block> x) {
  for (auto& stmt : x->statements) accept(stmt);
}

// Return
void Visitor::visit_return(ptr<ast::Return> x) {
  if (x->operand) accept(x->operand);
}

// Conditional
void Visitor::visit_conditional(ptr<ast::Conditional> x) {
  for (auto& br : x->branches) accept(br);
  if (x->otherwise) accept(x->otherwise);
}

// Conditional: Branch
void Visitor::visit_branch(ptr<ast::Branch> x) {
  accept(x->condition);
  accept(x->block);
}

// Repeat
void Visitor::visit_repeat(ptr<ast::Repeat> x) {
  accept(x->condition);
  accept(x->block);
}

// Call
void Visitor::visit_call(ptr<ast::Call> x) {
  accept(x->operand);
  for (auto& arg : x->arguments) accept(arg);
}

// Call: Argument
void Visitor::visit_argument(ptr<ast::Argument> x) {
  accept(x->value);
}

// Unary
void Visitor::visit_unary(ptr<ast::Unary> x) {
  accept(x->operand);
}

void Visitor::visit_identity(ptr<ast::Identity> x)      { visit_unary(x); }
void Visitor::visit_negate(ptr<ast::Negate> x)          { visit_unary(x); }
void Visitor::visit_bit_not(ptr<ast::BitNot> x)         { visit_unary(x); }
void Visitor::visit_indirect(ptr<ast::Indirect> x)      { visit_unary(x); }
void Visitor::visit_not(ptr<ast::Not> x)                { visit_unary(x); }
void Visitor::visit_address_of(ptr<ast::AddressOf> x)   { visit_unary(x); }

// Binary
void Visitor::visit_binary(ptr<ast::Binary> x) {
  accept(x->lhs);
  accept(x->rhs);
}

void Visitor::visit_add(ptr<ast::Add> x)                  { visit_binary(x); }
void Visitor::visit_sub(ptr<ast::Sub> x)                  { visit_binary(x); }
void Visitor::visit_mul(ptr<ast::Mul> x)                  { visit_binary(x); }
void Visitor::visit_div(ptr<ast::Div> x)                  { visit_binary(x); }
void Visitor::visit_mod(ptr<ast::Mod> x)                  { visit_binary(x); }
void Visitor::visit_eq(ptr<ast::EqualTo> x)               { visit_binary(x); }
void Visitor::visit_ne(ptr<ast::NotEqualTo> x)            { visit_binary(x); }
void Visitor::visit_lt(ptr<ast::LessThan> x)              { visit_binary(x); }
void Visitor::visit_lte(ptr<ast::LessThanOrEqualTo> x)    { visit_binary(x); }
void Visitor::visit_gte(ptr<ast::GreaterThanOrEqualTo> x) { visit_binary(x); }
void Visitor::visit_gt(ptr<ast::GreaterThan> x)           { visit_binary(x); }
void Visitor::visit_bit_and(ptr<ast::BitAnd> x)           { visit_binary(x); }
void Visitor::visit_bit_xor(ptr<ast::BitXor> x)           { visit_binary(x); }
void Visitor::visit_bit_or(ptr<ast::BitOr> x)             { visit_binary(x); }
void Visitor::visit_and(ptr<ast::And> x)                  { visit_binary(x); }
void Visitor::visit_or(ptr<ast::Or> x)                    { visit_binary(x); }
void Visitor::visit_assign(ptr<ast::Assign> x)            { visit_binary(x); }
