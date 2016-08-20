// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_BACK_BUILD_H
#define ARROW_BACK_BUILD_H

#include <memory>
#include <string>

#include "arrow/back/pass.hpp"

namespace arrow {
namespace back {

class Build : public Pass {
 public:
  using Pass::Pass;

  LLVMValueRef run(ptr<ir::Value>);

 private:
  LLVMValueRef handle_bool(ptr<ir::Boolean>);
  LLVMValueRef handle_int(ptr<ir::Integer>);
  LLVMValueRef handle_variable(ptr<ir::Variable>);

  LLVMValueRef handle_add(ptr<ir::Add>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_BACK_BUILD_H
