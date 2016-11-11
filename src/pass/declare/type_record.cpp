// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_type_record(ptr<ast::TypeRecord> x) {
  // Make: TypeRecord
  auto record = make<ir::TypeRecord>(x, x->name);

  // Scope: put
  _ctx.scope->put(x, record, record->name);
}
