// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_MIDDLE_DECLARE_H
#define ARROW_MIDDLE_DECLARE_H

#include "arrow/middle/pass.hpp"

namespace arrow {
namespace middle {

class Declare : public Pass {
 public:
  using Pass::Pass;

  ptr<ir::Item> run(ptr<ast::Node>);

 private:
  ptr<ir::Module> handle_module(ptr<ast::Module>);
  ptr<ir::Variable> handle_variable(ptr<ast::Variable>);
};

}  // namespace middle
}  // namespace arrow

#endif  // ARROW_MIDDLE_DECLARE_H
