// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::pass::Build;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(x))

auto Build::run(ptr<ast::Node> x) -> ptr<ir::Value> {
  Match(*x) {
    ACCEPT(ast::Module, module);
    ACCEPT(ast::Variable, variable);
    ACCEPT(ast::ExternFunction, extern_function);
    ACCEPT(ast::ExternVariable, extern_variable);
    ACCEPT(ast::Function, function);

    ACCEPT(ast::Name, name);
    ACCEPT(ast::Identifier, id);
    ACCEPT(ast::Path, path);
    ACCEPT(ast::Boolean, bool);
    ACCEPT(ast::Integer, int);
    ACCEPT(ast::String, str);
    ACCEPT(ast::Real, real);
    ACCEPT(ast::Unit, unit);
    ACCEPT(ast::ExpressionStatement, expression_statement);

    ACCEPT(ast::Indirect, indirect);
    ACCEPT(ast::AddressOf, address_of);

    ACCEPT(ast::Identity, identity);
    ACCEPT(ast::Negate, negate);

    ACCEPT(ast::Add, add);
    ACCEPT(ast::Sub, sub);
    ACCEPT(ast::Mul, mul);
    ACCEPT(ast::Div, div);
    ACCEPT(ast::Mod, mod);

    ACCEPT(ast::Assign, assign);
    ACCEPT(ast::AssignAdd, assign_add);
    ACCEPT(ast::AssignSub, assign_sub);
    ACCEPT(ast::AssignMul, assign_mul);
    ACCEPT(ast::AssignDiv, assign_div);
    ACCEPT(ast::AssignMod, assign_mod);
    ACCEPT(ast::AssignBitAnd, assign_bit_and);
    ACCEPT(ast::AssignBitOr, assign_bit_or);
    ACCEPT(ast::AssignBitXor, assign_bit_xor);

    ACCEPT(ast::Call, call);
    ACCEPT(ast::Argument, argument);
    ACCEPT(ast::Return, return);

    ACCEPT(ast::BitNot, bit_not);
    ACCEPT(ast::BitAnd, bit_and);
    ACCEPT(ast::BitOr, bit_or);
    ACCEPT(ast::BitXor, bit_xor);
    ACCEPT(ast::BitLeftShift, bit_left_shift);
    ACCEPT(ast::BitRightShift, bit_right_shift);

    ACCEPT(ast::Not, not);
    ACCEPT(ast::And, and);
    ACCEPT(ast::Or, or);

    ACCEPT(ast::EqualTo, eq);
    ACCEPT(ast::NotEqualTo, ne);
    ACCEPT(ast::LessThan, lt);
    ACCEPT(ast::LessThanOrEqualTo, le);
    ACCEPT(ast::GreaterThan, gt);
    ACCEPT(ast::GreaterThanOrEqualTo, ge);

    ACCEPT(ast::Import, import);
    ACCEPT(ast::TypeAlias, type_alias);

    ACCEPT(ast::CInclude, cinclude);

    ACCEPT(ast::Block, block);
    ACCEPT(ast::Conditional, conditional);
    ACCEPT(ast::Repeat, repeat);
    ACCEPT(ast::Break, break);
    ACCEPT(ast::Continue, continue);

    ACCEPT(ast::Transmute, transmute);

    Otherwise() {
      Log::get().error("Build not implemented for {}", typeid(*x).name());
    }
  } EndMatch;

  return nullptr;
}
