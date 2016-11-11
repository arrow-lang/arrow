// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;
using arrow::pass::TypeDeduce;

auto Build::_assign(
  ptr<ast::Binary> x,
  std::function<ptr<ir::Type>(ptr<ir::Value>, ptr<ir::Value>)> deduce,
  std::function<ptr<ir::Value>(ptr<ir::Type>, ptr<ir::Value>, ptr<ir::Value>)> make
) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Deduce the inherent operation (if any)
  auto type = deduce(lhs, rhs);
  if (!type) return nullptr;

  // Check the assignment (for type-equivalence)
  if (!ir::type_is_assignable(lhs->type, type)) {
    Log::get().error(x->span, "mismatched types: expected `{}`, found `{}`",
      lhs->type->name, type->name);

    return nullptr;
  }

  // Make: Assign<*>
  return make(lhs->type, lhs, rhs);
}

auto Build::handle_assign(ptr<ast::Assign> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) {
      return rhs->type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::Assign>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_add(ptr<ast::AssignAdd> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::Add>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `+`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignAdd>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_sub(ptr<ast::AssignSub> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::Sub>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `-`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignSub>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_mul(ptr<ast::AssignMul> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::Mul>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `*`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignMul>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_div(ptr<ast::AssignDiv> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::Div>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `/`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignDiv>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_mod(ptr<ast::AssignMod> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::Mod>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `%`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignMod>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_bit_and(ptr<ast::AssignBitAnd> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::BitAnd>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `&`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignBitAnd>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_bit_or(ptr<ast::AssignBitOr> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::BitOr>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `|`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignBitOr>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_bit_xor(ptr<ast::AssignBitXor> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::BitXor>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `^`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignBitXor>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_bit_left_shift(ptr<ast::AssignBitLeftShift> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::BitLeftShift>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `<<`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignBitLeftShift>(x, type, lhs, rhs);
    }
  );
}

auto Build::handle_assign_bit_right_shift(ptr<ast::AssignBitRightShift> x) -> ptr<ir::Value> {
  return _assign(x,
    [&](auto lhs, auto rhs) -> ptr<ir::Type> {
      auto type = TypeDeduce(_ctx).run(make<ast::BitRightShift>(x->span, x->lhs, x->rhs));
      if (!type) {
        Log::get().error(x->span,
          "unsupported operand types for `>>`: `{}` and `{}`",
          lhs->type->name, rhs->type->name);

        return nullptr;
      }

      return type;
    },
    [&](auto type, auto lhs, auto rhs){
      return make<ir::AssignBitRightShift>(x, type, lhs, rhs);
    }
  );
}
