// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeBuild;
namespace ast = arrow::ast;
using arrow::ptr;
using arrow::isa;
using arrow::cast;

auto TypeBuild::handle_name(ptr<ast::Name> x) -> ptr<ir::Type> {
  return ir::type_of(ir::resolve_name(_ctx, x));
}

auto TypeBuild::handle_type_name(ptr<ast::TypeName> x) -> ptr<ir::Type> {
  return handle_name(x->name);
}

auto TypeBuild::handle_path(ptr<ast::Path> x) -> ptr<ir::Type> {
  return ir::type_of(ir::resolve_path(_ctx, x));
}

auto TypeBuild::handle_type_path(ptr<ast::TypePath> x) -> ptr<ir::Type> {
  return handle_path(x->path);
}


// auto TypeBuild::handle_id(ptr<ast::Identifier> x) -> ptr<ir::Type> {
//   // Does this identifier exist
//   if (!_ctx.scope->contains(x->text)) {
//     Log::get().error(x->span, "unresolved name '{}'", x->text);
//     return nullptr;
//   }
//
//   // Get the item in reference
//   auto item = _ctx.scope->get(x->text);
//
//   auto item_t = cast<ir::Type>(item);
//   if (item_t == nullptr) {
//     Log::get().error(x->span, "'{}' is not a type", x->text);
//
//     return nullptr;
//   }
//
//   return item_t;
// }
//
// static bool expand_path(ptr<ast::Node> node, std::vector<ptr<ast::Name>>& result) {
//   if (isa<ast::Name>(node)) {
//     result.push_back(cast<ast::Name>(node));
//   } else if (isa<ast::Path>(node)) {
//     auto path = cast<ast::Path>(node);
//
//     // Add LHS
//     if (!expand_path(path->operand, result)) return false;
//
//     // ADD RHS
//     result.push_back(path->member);
//   } else {
//     return false;
//   }
//
//   return true;
// }
//
// auto TypeBuild::handle_path(ptr<ast::Path> x) -> ptr<ir::Type> {
//   if (isa<ast::Name>(x->operand)) {
//     // Build ast::TypePath from ast::Path
//     auto result = make<ast::TypePath>(x->span);
//     if (!expand_path(x, result->segments)) return nullptr;
//
//     return handle_type_path(result);
//   }
//
//   return nullptr;
// }
//
// auto TypeBuild::handle_type_path(ptr<ast::TypePath> x) -> ptr<ir::Type> {
//   // No segments ?
//   if (x->segments.size() == 0) return nullptr;
//
//   // Handle the first segment
//   auto segment0 = x->segments[0];
//   // Does this identifier exist
//   if (!_ctx.scope->contains(segment0->text)) {
//     Log::get().error(segment0->span, "unresolved name `{}`", segment0->text);
//     return nullptr;
//   }
//
//   // Get the item in reference
//   ptr<ir::Node> res = _ctx.scope->get(segment0->text);
//   if (!res) return nullptr;
//
//   // Iterate through remaining segments
//   for (unsigned i = 1; i < x->segments.size(); ++i) {
//     auto name = x->segments[i];
//
//     // Check for the member in the current value
//     Match(*res) {
//       Case(mch::C<ir::Import>()) {
//         // Module import .. access inside the module
//         auto imp = cast<ir::Import>(res);
//         auto tmp = imp->module->block->scope->get(name->text);
//         if (!tmp) {
//           Log::get().error(name->span, "module '{}' has no member '{}'",
//             imp->name, name->text);
//         }
//
//         res = tmp;
//       } break;
//
//       Otherwise() {
//         // Unhandled
//         // TODO: Better error message
//         Log::get().error(name->span, "`{}` has no member '{}'",
//           type_of(res)->name, name->text);
//
//         return nullptr;
//       }
//     } EndMatch
//   }
//
//   auto res_t = cast<ir::Type>(res);
//   if (res_t == nullptr) {
//     std::stringstream stream;
//     for (unsigned i = 0; i < x->segments.size(); ++i) {
//       if (i > 0) stream << ".";
//       stream << x->segments[i]->text;
//     }
//
//     Log::get().error(x->span, "'{}' is not a type", stream.str());
//
//     return nullptr;
//   }
//
//   return res_t;
// }
