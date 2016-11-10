// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "llvm.hpp"
#include "mach7.hpp"

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_id(ptr<ast::Identifier> x) -> ptr<ir::Value> {
  // Does this identifier exist
  if (!_ctx.scope->contains(x->text)) {
    Log::get().error(x->span, "unresolved name `{}`", x->text);
    return nullptr;
  }

  // Get the item in reference
  auto item = _ctx.scope->get(x->text);

  // Return
  return cast<ir::Value>(item);
}

auto Build::handle_name(ptr<ast::Name> x) -> ptr<ir::Value> {
  // Does this identifier exist
  if (!_ctx.scope->contains(x->text)) {
    Log::get().error(x->span, "unresolved name `{}`", x->text);
    return nullptr;
  }

  // Get the item in reference
  auto item = _ctx.scope->get(x->text);

  // IF we have a generic item
  auto gitem = cast<ir::Generic>(item);
  if (gitem) {
    // Instantiate and return the concrete item
    item = gitem->instantiate(_ctx, x->type_arguments);
  }

  // Return
  return cast<ir::Value>(item);
}

auto Build::handle_path(ptr<ast::Path> x) -> ptr<ir::Value> {
  // No segments ?
  if (x->segments.size() == 0) return nullptr;

  // Handle the first segment
  auto segment0 = x->segments[0];
  // Does this identifier exist
  if (!_ctx.scope->contains(segment0->text)) {
    Log::get().error(segment0->span, "unresolved name `{}`", segment0->text);
    return nullptr;
  }

  // Get the item in reference
  ptr<ir::Node> res = _ctx.scope->get(segment0->text);

  // 1 segment ?
  if (x->segments.size() == 1) return cast<ir::Value>(res);

  // Iterate through remaining segments
  for (unsigned i = 1; i < x->segments.size(); ++i) {
    auto name = x->segments[i];

    // Check for the member in the current value
    Match(*res) {
      Case(mch::C<ir::Import>()) {
        // Module import .. access inside the module
        auto imp = cast<ir::Import>(res);
        auto tmp = imp->module->block->scope->get(name->text);
        if (!tmp) {
          Log::get().error(name->span, "module '{}' has no member '{}'",
            imp->name, name->text);
        }

        // IF we have a generic item
        auto gitem = cast<ir::Generic>(tmp);
        if (gitem) {
          // Instantiate and return the concrete item
          tmp = gitem->instantiate(_ctx, name->type_arguments);
        }

        res = tmp;
      } break;

      Otherwise() {
        // Unhandled
        // TODO: Better error message
        Log::get().error(name->span, "`{}` has no member '{}'",
          type_of(res)->name, name->text);

        return nullptr;
      }
    } EndMatch
  }

  // Return
  return cast<ir::Value>(res);
}
