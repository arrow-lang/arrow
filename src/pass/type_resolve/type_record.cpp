// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_type_record(ptr<ast::TypeRecord> x) {
  // Get: TypeRecord
  auto record = _ctx.scope->get<ir::TypeRecord>(x);
  if (!record) return;

  // Scope: Enter
  auto sb = ir::Scope::enter(record->scope, _ctx);

  // Enumerate members ..
  record->members.clear();
  for (auto member : x->members) {
    // Build: type
    auto member_t = TypeBuild(_ctx).run(member->type);
    if (!member_t) {
      _incomplete = true;
      return;
    }

    record->members.push_back(make<ir::TypeRecordMember>(
      member,
      member->name,
      member_t
    ));
  }

  // Scope: Exit
  sb.exit();
}
