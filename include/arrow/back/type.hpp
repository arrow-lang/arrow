// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_BACK_TYPE_H
#define ARROW_BACK_TYPE_H

#include <memory>
#include <string>

#include "arrow/back/pass.hpp"

namespace arrow {
namespace back {

class Type : public Pass {
 public:
  using Pass::Pass;

  LLVMTypeRef run(ptr<ir::Type>);

 private:
  LLVMTypeRef handle_bool(ptr<ir::TypeBoolean>);
  LLVMTypeRef handle_int(ptr<ir::TypeInteger>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_BACK_TYPE_H
