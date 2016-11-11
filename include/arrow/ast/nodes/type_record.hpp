// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPE_RECORD_H
#define ARROW_AST_TYPE_RECORD_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/type.hpp"
#include "arrow/ast/nodes/statement.hpp"

namespace arrow {
namespace ast {

struct TypeRecordMember : Statement {
  TypeRecordMember(Span span, std::string name, ptr<Type> type)
    : Statement(span), name(name), type(type) {
  }

  virtual ~TypeRecordMember() noexcept;

  /// Name
  std::string name;

  /// Type
  ptr<Type> type;
};

struct TypeRecord : Statement {
  TypeRecord(Span span, std::string name, std::vector<ptr<TypeRecordMember>> members)
    : Statement(span), name(name), members(members) {
  }

  virtual ~TypeRecord() noexcept;

  /// Name
  std::string name;

  /// Members
  std::vector<ptr<TypeRecordMember>> members;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPE_RECORD_H
