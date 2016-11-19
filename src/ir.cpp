// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/log.hpp"
#include "arrow/pass/build.hpp"
#include "arrow/pass/type_deduce.hpp"
#include "mach7.hpp"
#include "fmt.hpp"

namespace ir = arrow::ir;

ir::Node::~Node() noexcept { }
ir::Item::~Item() noexcept { }
ir::Module::~Module() noexcept { }
ir::Block::~Block() noexcept { }
ir::Variable::~Variable() noexcept { }
ir::Function::~Function() noexcept { }
ir::Import::~Import() noexcept { }
ir::Parameter::~Parameter() noexcept { }
ir::ExternFunction::~ExternFunction() noexcept { }
ir::ExternVariable::~ExternVariable() noexcept { }
ir::Constant::~Constant() noexcept { }

ir::GenericTypeParameter::~GenericTypeParameter() noexcept { }
ir::GenericFunction::~GenericFunction() noexcept { }
ir::Generic::~Generic() noexcept { }

ir::Type::~Type() noexcept { }
ir::TypeInteger::~TypeInteger() noexcept { }
ir::TypeBoolean::~TypeBoolean() noexcept { }
ir::TypeReal::~TypeReal() noexcept { }
ir::TypeLiteralInteger::~TypeLiteralInteger() noexcept { }
ir::TypeLiteralReal::~TypeLiteralReal() noexcept { }
ir::TypeFunction::~TypeFunction() noexcept { }
ir::TypeExternFunction::~TypeExternFunction() noexcept { }
ir::TypeString::~TypeString() noexcept { }
ir::TypePointer::~TypePointer() noexcept { }
ir::TypeAlias::~TypeAlias() noexcept { }
ir::TypeUnit::~TypeUnit() noexcept { }
ir::TypeDivergent::~TypeDivergent() noexcept { }
ir::TypeRecord::~TypeRecord() noexcept { }
ir::TypeRecordMember::~TypeRecordMember() noexcept { }

ir::Value::~Value() noexcept { }
ir::Unit::~Unit() noexcept { }
ir::Transmute::~Transmute() noexcept { }
ir::Integer::~Integer() noexcept { }
ir::Real::~Real() noexcept { }
ir::String::~String() noexcept { }
ir::Boolean::~Boolean() noexcept { }
ir::RecordMember::~RecordMember() noexcept { }

ir::AddressOf::~AddressOf() noexcept {}
ir::Indirect::~Indirect() noexcept {}

ir::Unary::~Unary() noexcept {}
ir::Negate::~Negate() noexcept {}

ir::Binary::~Binary() noexcept {}
ir::Add::~Add() noexcept {}
ir::Sub::~Sub() noexcept {}
ir::Mul::~Mul() noexcept {}
ir::Div::~Div() noexcept {}
ir::Mod::~Mod() noexcept {}

ir::Assign::~Assign() noexcept {}
ir::AssignAdd::~AssignAdd() noexcept {}
ir::AssignSub::~AssignSub() noexcept {}
ir::AssignMul::~AssignMul() noexcept {}
ir::AssignDiv::~AssignDiv() noexcept {}
ir::AssignMod::~AssignMod() noexcept {}
ir::AssignBitAnd::~AssignBitAnd() noexcept {}
ir::AssignBitOr::~AssignBitOr() noexcept {}
ir::AssignBitXor::~AssignBitXor() noexcept {}
ir::AssignBitLeftShift::~AssignBitLeftShift() noexcept {}
ir::AssignBitRightShift::~AssignBitRightShift() noexcept {}

ir::Call::~Call() noexcept {}
ir::Return::~Return() noexcept {}

ir::BitNot::~BitNot() noexcept {}
ir::BitAnd::~BitAnd() noexcept {}
ir::BitOr::~BitOr() noexcept {}
ir::BitXor::~BitXor() noexcept {}
ir::BitLeftShift::~BitLeftShift() noexcept {}
ir::BitRightShift::~BitRightShift() noexcept {}

ir::Not::~Not() noexcept {}
ir::And::~And() noexcept {}
ir::Or::~Or() noexcept {}

ir::Repeat::~Repeat() noexcept {}
ir::Conditional::~Conditional() noexcept {}
ir::Break::~Break() noexcept {}
ir::Continue::~Continue() noexcept {}

ir::EqualTo::~EqualTo() noexcept {}
ir::NotEqualTo::~NotEqualTo() noexcept {}
ir::LessThan::~LessThan() noexcept {}
ir::LessThanOrEqualTo::~LessThanOrEqualTo() noexcept {}
ir::GreaterThan::~GreaterThan() noexcept {}
ir::GreaterThanOrEqualTo::~GreaterThanOrEqualTo() noexcept {}

// Reduce 2 types following simple rules
arrow::ptr<ir::Type> arrow::ir::type_reduce(ptr<ir::Type> a, ptr<ir::Type> b) {
  // Same type
  if (a->is_equal(b)) return a;

  // Integer + Integer OR Real + Real
  if (
    (a->is_real() && b->is_real()) ||
    (a->is_integer() && b->is_integer())
  ) {
    // Handle is_equal
    if (a->is_equal(b)) return a;

    // Handle a (Literal) on either side; the type should go
    // to the other side
    if (a->size() == 0 && b->size() > 0) {
      return b;
    }

    if (b->size() == 0 && a->size() > 0) {
      return a;
    }
  }

  // Real + Literal Integer
  if (
    a->is_real() && b->is_integer() &&
    b->size() == 0
  ) {
    return a;
  }

  // Literal Integer + Real
  if (
    b->is_real() && a->is_integer() &&
    a->size() == 0
  ) {
    return b;
  }

  return nullptr;
}

// Check if type RHS is assignable to type LHS
bool arrow::ir::type_is_assignable(ptr<ir::Type> lhs, ptr<ir::Type> rhs) {
  return (
    // Nil
    (lhs && rhs) && (
    // Equal
    (lhs->is_equal(rhs)) ||
    // Divergent
    (rhs->is_divergent()) ||
    // Integer & Literal Integer
    (
      lhs->is_integer() && rhs->is_integer() &&
      (lhs->size() == 0 || rhs->size() == 0)
    ) ||
    // Real & Literal Real
    (
      lhs->is_real() && rhs->is_real() &&
      (lhs->size() == 0 || rhs->size() == 0)
    ) ||
    // Real & Literal Integer
    (lhs->is_real() && rhs->is_integer() && rhs->size() == 0) ||
    // Alias := Literal
    (lhs->tag() == ARROW_TTAG_ALIAS && rhs->size() == 0 &&
      type_is_assignable(type_canonical(lhs), rhs))
  ));
}

// Get canonical type
auto arrow::ir::type_canonical(ptr<Type> type) -> ptr<Type> {
  if (!type) return nullptr;

  Match(*type) {
    Case(mch::C<ir::TypeAlias>()) {
      auto type_alias = cast<ir::TypeAlias>(type);
      return type_alias->target;
    }

    Otherwise() {
      return type;
    }
  } EndMatch;

  return type;
}

// Transmute shorthand
auto arrow::ir::transmute(ptr<Value> operand, ptr<Type> type) -> ptr<ir::Value> {
  return make<Transmute>(operand->source, operand, type);
}

// Parse CC
int arrow::ir::parse_call_conv(arrow::Span span, std::string ccs) {
  int cc = -1;
  if (ccs == "C" || ccs == "cdecl") {
    cc = LLVMCCallConv;
  } else if (ccs == "stdcall") {
    cc = LLVMX86StdcallCallConv;
  } else if (ccs == "fastcall") {
    cc = LLVMX86FastcallCallConv;
  } else if (ccs == "vectorcall") {
    cc = 80;
  } else if (ccs == "win64") {
    cc = 79;
  } else {
    Log::get().error(
      span,
      "invalid ABI: expected one of [C, cdecl, stdcall, fastcall, "
      " vectorcall, win64], found `{}`", ccs);

    return -1;
  }

  return cc;
}

// Resolve NAME expression (into value)
auto arrow::ir::resolve_name(GContext& ctx, ptr<ast::Name> name, bool silent) -> ptr<Node> {
  // Check for existance in-scope
  if (!ctx.scope->contains(name->text)) {
    if (!silent) Log::get().error(name->span, "unresolved name `{}`", name->text);
    return nullptr;
  }

  // Get the item from scope
  auto result = ctx.scope->get(name->text);

  // If we have a generic item; instantiate
  // TODO: Error checking here
  if (isa<ir::Generic>(result)) {
    result = cast<ir::Generic>(result)->instantiate(
      ctx, name->type_arguments);
  }

  return result;
}

// Resolve PATH expression
auto arrow::ir::resolve_path(GContext& ctx, ptr<ast::Path> x, bool silent, bool build) -> ptr<Node> {
  // Resolve the path operand
  ptr<ir::Node> op;
  ptr<ir::Type> op_t;

  if (isa<ast::Name>(x->operand)) {
    op = resolve_name(ctx, cast<ast::Name>(x->operand), silent);
    if (!op) return nullptr;
    op_t = ir::type_of(op);
  } else {
    // Run the normal passes (if not a name)
    if (build) {
      op = pass::Build(ctx).run(x->operand);
      if (!op) return nullptr;
      op_t = cast<ir::Value>(op)->type;
    } else {
      op_t = pass::TypeDeduce(ctx).run(x->operand);
      if (!op_t) return nullptr;
    }
  }

  ptr<ir::Node> result;

  // Check for a qualified name reference
  if (op != nullptr && isa<ir::Import>(op)) {
    // Module import .. access inside the module
    auto import = cast<ir::Import>(op);
    auto tmp = import->module->block->scope->get(x->member->text);
    if (!tmp) {
      if (!silent) {
        Log::get().error(x->member->span, "module `{}` has no member `{}`",
          import->name, x->member->text);
      }

      return nullptr;
    }

    // If we have a generic item; instantiate
    if (isa<ir::Generic>(tmp)) {
      tmp = cast<ir::Generic>(tmp)->instantiate(
        ctx, x->member->type_arguments);
    }

    result = tmp;
  } else if (op_t != nullptr) {
    Match(*op_t) {
      Case(mch::C<ir::TypeRecord>()) {
        auto record = cast<ir::TypeRecord>(op_t);
        auto member_index = record->member_index_of(x->member->text);
        if (member_index < 0) {
          if (!silent) {
            Log::get().error(x->member->span, "`{}` has no member `{}`",
              op_t->name, x->member->text);
          }

          return nullptr;
        }

        result = make<ir::RecordMember>(x->member,
          record->members[member_index]->type, cast<ir::Value>(op),
          member_index);
      } break;

      Otherwise() {
        if (!silent) {
          Log::get().error(x->member->span, "`{}` has no member `{}`",
            op_t->name, x->member->text);
        }

        return nullptr;
      } break;
    } EndMatch
  }

  return result;
}
