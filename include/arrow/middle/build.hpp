// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_MIDDLE_BUILD_H
#define ARROW_MIDDLE_BUILD_H

#include "arrow/middle/pass.hpp"

namespace arrow {
namespace middle {

class Build : public Pass {
 public:
  using Pass::Pass;

  void run(ptr<ast::Node>);

 private:
  void handle_int(ptr<ast::Integer>);
  void handle_bool(ptr<ast::Boolean>);
};

}  // namespace middle
}  // namespace arrow

#endif  // ARROW_MIDDLE_BUILD_H
