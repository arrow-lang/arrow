// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_conditional(ptr<ast::Conditional> x) -> ptr<ir::Value> {
  ptr<ir::Value> result = nullptr;
  int i = x->branches.size() - 1;

  // Check if this block is an expression 
  auto is_expression = x->is_expression || (!_expression_c.empty() && _expression_c.top());
  auto ec = _expression_c.enter(is_expression);

  // Check for a missing ELSE if this is an expression
  if (is_expression && !x->otherwise) {
    Log::get().error(x->span, "if expression missing an else clause");

    return nullptr;
  }

  // Determine the type (of the entire conditional)
  auto ctype = TypeDeduce(_ctx).run(x);
  if (!ctype) ctype = nullptr;

  // Type check the branches (if we are an expression)
  if (is_expression) {
    auto fail = false;

    // Branches
    for (auto& br : x->branches) {
      auto type = TypeDeduce(_ctx).run(br);

      // Assignment must be type equivalent
      if (!ir::type_is_assignable(ctype, type)) {
        Log::get().error(
          br->block->statements[br->block->statements.size() - 1]->span, 
          "mismatched types: expected `{}`, found `{}`",
          ctype->name, type->name);

        fail = true;
      }
    }

    // Otherwise
    if (x->otherwise) {
      auto type = TypeDeduce(_ctx).run(x->otherwise);

      // Assignment must be type equivalent
      if (!ir::type_is_assignable(ctype, type)) {
        Log::get().error(
          x->otherwise->statements[x->otherwise->statements.size() - 1]->span, 
          "mismatched types: expected `{}`, found `{}`",
          ctype->name, type->name);

        fail = true;
      }
    }

    if (fail) return nullptr;
  }


  do {
  	auto br = x->branches.at(i);
  	i -= 1;

  	auto condition = run(br->condition);
  	if (!condition) return nullptr;

  	auto then = run(br->block);
  	if (!then) return nullptr;

  	auto otherwise = result;
  	if (!otherwise) {
  		if (x->otherwise) {
  			otherwise = run(x->otherwise);
  			if (!otherwise) return nullptr;
  		}
  	}

  	// TODO: Need to make source a SPAN

  	result = make<ir::Conditional>(x, ctype, condition, then, otherwise, is_expression);
  } while (i >= 0);

  return result;
}
