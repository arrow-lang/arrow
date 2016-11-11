// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_PRINT_H
#define ARROW_AST_PRINT_H

#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include "arrow/ast/nodes.hpp"

namespace arrow {
namespace ast {

class Print {
 public:
  Print();

  Print(const Print& other) = delete;
  Print(Print&& other) = delete;

  Print& operator=(const Print& other) = delete;
  Print& operator=(Print&& other) = delete;

  virtual ~Print() noexcept;

  void run(ptr<Node> node);

 private:
  void print(ptr<Node>);
  void print_module(ptr<Module>);
  void print_variable(ptr<Variable>);
  void print_expression_statement(ptr<ExpressionStatement>);
  void print_return(ptr<Return>);
  void print_block(ptr<Block>);

  void print_integer(ptr<Integer>);
  void print_real(ptr<Real>);
  void print_bool(ptr<Boolean>);
  void print_str(ptr<String>);
  void print_name(ptr<Name>);
  void print_path(ptr<Path>);
  void print_id(ptr<Identifier>);
  void print_tuple(ptr<Tuple>);

  void print_identity(ptr<Identity>);
  void print_negate(ptr<Negate>);
  void print_bit_not(ptr<BitNot>);
  void print_not(ptr<Not>);
  void print_indirect(ptr<Indirect>);
  void print_address_of(ptr<AddressOf>);

  void print_mul(ptr<Mul> n);
  void print_div(ptr<Div> n);
  void print_mod(ptr<Mod> n);
  void print_add(ptr<Add> n);
  void print_sub(ptr<Sub> n);
  void print_bit_and(ptr<BitAnd> n);
  void print_bit_xor(ptr<BitXor> n);
  void print_bit_or(ptr<BitOr> n);
  void print_gte(ptr<GreaterThanOrEqualTo> n);
  void print_gt(ptr<GreaterThan> n);
  void print_lt(ptr<LessThan> n);
  void print_lte(ptr<LessThanOrEqualTo> n);
  void print_eq(ptr<EqualTo> n);
  void print_ne(ptr<NotEqualTo> n);
  void print_and(ptr<And> n);
  void print_or(ptr<Or> n);
  void print_assign(ptr<Assign> n);
  void print_assign_add(ptr<AssignAdd> n);
  void print_assign_sub(ptr<AssignSub> n);
  void print_assign_mul(ptr<AssignMul> n);
  void print_assign_div(ptr<AssignDiv> n);
  void print_assign_mod(ptr<AssignMod> n);
  void print_assign_bit_or(ptr<AssignBitOr> n);
  void print_assign_bit_and(ptr<AssignBitAnd> n);
  void print_assign_bit_xor(ptr<AssignBitXor> n);

  void print_type_name(ptr<TypeName>);
  void print_type_path(ptr<TypePath>);
  void print_type_pointer(ptr<TypePointer>);
  void print_type_alias(ptr<TypeAlias>);
  void print_type_tuple(ptr<TypeTuple>);
  void print_type_function(ptr<TypeFunction>);
  void print_type_record(ptr<TypeRecord>);
  void print_type_record_member(ptr<TypeRecordMember>);

  void print_function(ptr<Function>);
  void print_extern_function(ptr<ExternFunction>);
  void print_extern_variable(ptr<ExternVariable>);
  void print_parameter(ptr<Parameter>);
  void print_type_parameter(ptr<TypeParameter>);

  void print_import(ptr<Import>);

  void print_cinclude(ptr<CInclude>);

  void print_call(ptr<Call>);
  void print_argument(ptr<Argument>);

  void print_repeat(ptr<Repeat>);
  void print_conditional(ptr<Conditional>);
  void print_branch(ptr<Branch>);
  void print_break(ptr<Break>);
  void print_continue(ptr<Continue>);

  void print_transmute(ptr<Transmute>);
  void print_unit(ptr<Unit>);
  void print_type_unit(ptr<TypeUnit>);

  void handle(
    const char* name, ptr<Node> n, std::function<void()> handle);

  void handle_unary(const char* name, ptr<Unary> n);
  void handle_binary(const char* name, ptr<Binary> n);

  rapidjson::StringBuffer _s;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> _w;
};

/// Helper function to construct and use an AST Printer.
inline void print(ptr<Node> node) {
  Print().run(node);
}

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_PRINT_H
