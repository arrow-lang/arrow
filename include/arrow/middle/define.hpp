// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_MIDDLE_DEFINE_H
#define ARROW_MIDDLE_DEFINE_H

#include "arrow/middle/pass.hpp"

namespace arrow {
namespace middle {

class Define : public Pass {
 public:
  using Pass::Pass;

  void run(ptr<ir::Module>);

 private:
  void handle_module(ptr<ir::Module>);
  void handle_variable(ptr<ir::Variable>);
};

}  // namespace middle
}  // namespace arrow

#endif  // ARROW_MIDDLE_DEFINE_H
