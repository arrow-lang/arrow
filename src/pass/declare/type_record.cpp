// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_type_record(ptr<ast::TypeRecord> x) {
  // Is this record generic ?
  if (x->type_parameters.size() > 0) {
    // Yes..

    // Gather type parameters (just names really at this point)
    std::vector<ptr<ir::GenericTypeParameter>> type_parameters;
    for (auto const& p : x->type_parameters) {
      type_parameters.push_back(make<ir::GenericTypeParameter>(
        p, p->name
      ));
    }

    // Make: GenericTypeRecord
    auto record = make<ir::GenericTypeRecord>(
      x, x->name, type_parameters, _ctx.scope);

    // Scope: put
    _ctx.scope->put(x, record, record->name);

    return;
  }

  // Make: TypeRecord
  auto record = make<ir::TypeRecord>(x, x->name, _ctx.scope);

  // Scope: put
  _ctx.scope->put(x, record, record->name);
}
