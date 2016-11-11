// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_H
#define ARROW_IR_TYPE_H

#include <memory>
#include <string>

#include "llvm.hpp"
#include "arrow/ir/item.hpp"

namespace arrow {

struct GContext;

namespace ir {

enum TypeTag : unsigned {
  ARROW_TTAG_ALIAS,
  ARROW_TTAG_BOOLEAN,
  ARROW_TTAG_FUNCTION,
  ARROW_TTAG_EXTERN_FUNCTION,
  ARROW_TTAG_INTEGER,
  ARROW_TTAG_LITERAL_INTEGER,
  ARROW_TTAG_LITERAL_REAL,
  ARROW_TTAG_POINTER,
  ARROW_TTAG_REAL,
  ARROW_TTAG_STRING,
  ARROW_TTAG_UNIT,
  ARROW_TTAG_RECORD,
  ARROW_TTAG_RECORD_MEMBER,
};

struct Type : Item {
  Type(std::string name)
    : Node(nullptr), Item(name) {
  }

  virtual ~Type() noexcept;

  // Get LLVM handle
  virtual LLVMTypeRef handle(GContext&) noexcept = 0;

  virtual unsigned tag() const noexcept = 0;

  virtual bool is_equal(ptr<Type> other) const {
    return tag() == other->tag();
  }

  // Undefined for most types
  virtual bool is_signed() const {
    return false;
  }

  virtual bool is_unit() const {
    return false;
  }

  virtual bool is_divergent() const {
    return false;
  }

  // Size (in bits)
  virtual unsigned size() const {
    return 0;
  }

  // Test for type categories
  virtual bool is_boolean() const {
    return false;
  }

  virtual bool is_pointer() const {
    return false;
  }

  virtual bool is_integer() const {
    return false;
  }

  virtual bool is_real() const {
    return false;
  }

  virtual bool is_function() const {
    return false;
  }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_H
