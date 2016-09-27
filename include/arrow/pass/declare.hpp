// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_DECLARE_H
#define ARROW_DECLARE_H

#include <memory>
#include <string>

#include "arrow/pass.hpp"

namespace arrow {
namespace pass {

class Declare : public Pass {
 public:
  using Pass::Pass;

  void run(ptr<ast::Node>);

 private:
  void handle_module(ptr<ast::Module>);
  ptr<ir::Block> handle_block(ptr<ast::Block>);
  void handle_variable(ptr<ast::Variable>);
  void handle_function(ptr<ast::Function>);
  void handle_extern_function(ptr<ast::ExternFunction>);
};

}  // namespace back
}  // namespace arrow

#endif  // ARROW_DECLARE_H
