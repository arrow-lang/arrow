// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_conversion(
  ptr<ast::Expression> operand, ptr<ir::Type> type
) -> ptr<ir::Value> {
  auto value = run(operand);
  if (!value) return nullptr;

  return make<ir::Transmute>(value, type);
}
