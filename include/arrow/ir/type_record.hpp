// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_RECORD_H
#define ARROW_IR_TYPE_RECORD_H

#include <memory>
#include <string>
#include <sstream>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeRecordMember : Type {
  explicit TypeRecordMember(ptr<ast::Node> source, std::string name, ptr<Type> type)
    : Node(source), Type(name), type(type) {
  }

  virtual ~TypeRecordMember() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_RECORD_MEMBER;
  }

  virtual LLVMTypeRef handle(GContext& ctx) noexcept {
    return type->handle(ctx);
  }

  ptr<Type> type;
};

struct TypeRecord : Type {
  TypeRecord(ptr<ast::Node> source, std::string name)
    : Node(source), Type(name), members(), _handle(nullptr) {
  }

  virtual ~TypeRecord() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_RECORD;
  }

  virtual LLVMTypeRef handle(GContext& ctx) noexcept;

  int member_index_of(const std::string& text) {
    for (unsigned i = 0; i < members.size(); ++i) {
      if (members[i]->name == text) {
        return (int)i;
      }
    }

    return -1;
  }

  std::vector<ptr<TypeRecordMember>> members;

 private:
  LLVMTypeRef _handle;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_RECORD_H
