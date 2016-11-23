// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_implement(ptr<ast::Implement> x) {
  // Is this generic ?
  if (x->type_parameters.size() > 0) {
    // Yes..

    // Gather type parameters
    std::vector<ptr<ir::GenericTypeParameter>> type_parameters;
    for (auto const& p : x->type_parameters) {
      type_parameters.push_back(make<ir::GenericTypeParameter>(
        p, p->name
      ));
    }

    // Make: GenericImplement
    auto impl = make<ir::GenericImplement>(
      x, type_parameters, _ctx.scope);

    // Scope: put
    _ctx.scope->put(x, impl, "");

    // Register generic impl (in context)
    _ctx.impl_g.push_back(impl);

    return;
  }

  // Declare a impl ..
  // TODO: Interface (constraint)
  auto impl = make<ir::Implement>(x, _ctx.scope);

  // Add block to scope for later get
  _ctx.scope->put(x, impl, "");

  // Scope: Enter
  auto sb = ir::Scope::enter(impl->scope, _ctx);

  // Resolve the target type
  auto target = ir::resolve_name(_ctx, x->target, false);
  if (!target) return;
  auto target_t = ir::type_of(target);
  if (!target_t) return;

  // Register impl (in context)
  _ctx.impl[target_t.get()].push_back(impl);

  // Namespace: Push
  _ctx.ns.push_front(target_t->name);

  // TODO: Assert that the target type is in the current module (file)

  // Add `Self` to implement scope
  _ctx.scope->put(x, target_t, "Self");

  // Iterate through each function ..
  for (auto& function : x->functions) run(function);

  // Scope: Exit
  sb.exit();

  // Namespace: Pop
  _ctx.ns.pop_front();
}
