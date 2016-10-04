// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_deduce.hpp"

using arrow::pass::Build;

auto Build::handle_conditional(ptr<ast::Conditional> x) -> ptr<ir::Value> {
  ptr<ir::Value> result = nullptr;
  int i = x->branches.size() - 1;

  // Determine the type (of the entire conditional)
  auto ctype = TypeDeduce(_ctx).run(x);
  if (!ctype) ctype = nullptr;

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

  	result = make<ir::Conditional>(x, ctype, condition, then, otherwise);
  } while (i >= 0);

  return result;
}
