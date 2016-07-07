// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_BACK_DEFINE_H
#define ARROW_BACK_DEFINE_H

#include <memory>
#include <string>

#include "arrow/back/pass.hpp"

namespace arrow {
namespace back {

class Define : public Pass {
 public:
  using Pass::Pass;

  void run(ptr<ir::Item>);

 private:
  void handle_variable(ptr<ir::Variable>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_BACK_DEFINE_H
