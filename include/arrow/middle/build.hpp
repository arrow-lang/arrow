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

  ptr<ir::Value> run(ptr<ast::Node>);

 private:
  ptr<ir::Value> handle_int(ptr<ast::Integer>);
  ptr<ir::Value> handle_bool(ptr<ast::Boolean>);
  ptr<ir::Value> handle_id(ptr<ast::Identifier>);

  ptr<ir::Value> handle_add(ptr<ast::Add>);
};

}  // namespace middle
}  // namespace arrow

#endif  // ARROW_MIDDLE_BUILD_H
