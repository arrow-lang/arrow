// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/log.hpp"
#include "arrow/pass/build.hpp"
#include "arrow/pass/type_deduce.hpp"
#include "arrow/pass/type_build.hpp"
#include "mach7.hpp"
#include "fmt.hpp"

#define IMPL(N) \
  ir::N::~N() noexcept { }

using namespace arrow;
namespace ir = arrow::ir;
namespace ast = arrow::ast;

IMPL(Add)
IMPL(AddressOf)
IMPL(And)
IMPL(Assign)
IMPL(AssignAdd)
IMPL(AssignBitAnd)
IMPL(AssignBitLeftShift)
IMPL(AssignBitOr)
IMPL(AssignBitRightShift)
IMPL(AssignBitXor)
IMPL(AssignDiv)
IMPL(AssignMod)
IMPL(AssignMul)
IMPL(AssignSub)
IMPL(Binary)
IMPL(BitAnd)
IMPL(BitLeftShift)
IMPL(BitNot)
IMPL(BitOr)
IMPL(BitRightShift)
IMPL(BitXor)
IMPL(Block)
IMPL(Boolean)
IMPL(Break)
IMPL(Call)
IMPL(Conditional)
IMPL(Constant)
IMPL(Continue)
IMPL(Div)
IMPL(EqualTo)
IMPL(ExternFunction)
IMPL(ExternVariable)
IMPL(IFunction)
IMPL(Function)
IMPL(Generic)
IMPL(GenericFunction)
IMPL(GenericTypeParameter)
IMPL(GenericTypeRecord)
IMPL(GenericImplement)
IMPL(GenericInstantiation)
IMPL(GreaterThan)
IMPL(GreaterThanOrEqualTo)
IMPL(Implement)
IMPL(Import)
IMPL(Indirect)
IMPL(Integer)
IMPL(Item)
IMPL(LessThan)
IMPL(LessThanOrEqualTo)
IMPL(Mod)
IMPL(Module)
IMPL(Mul)
IMPL(Negate)
IMPL(Node)
IMPL(Not)
IMPL(Method)
IMPL(NotEqualTo)
IMPL(Or)
IMPL(Parameter)
IMPL(Real)
IMPL(RecordMember)
IMPL(Repeat)
IMPL(Return)
IMPL(String)
IMPL(Sub)
IMPL(Transmute)
IMPL(Type)
IMPL(TypeAlias)
IMPL(TypeBoolean)
IMPL(TypeDivergent)
IMPL(TypeExternFunction)
IMPL(TypeFunction)
IMPL(TypeInteger)
IMPL(TypeLiteralInteger)
IMPL(TypeLiteralReal)
IMPL(TypePointer)
IMPL(TypeReal)
IMPL(TypeRecord)
IMPL(TypeRecordMember)
IMPL(TypeString)
IMPL(TypeUnit)
IMPL(Unary)
IMPL(Unit)
IMPL(Value)
IMPL(Variable)

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
auto arrow::ir::resolve_name(GContext& ctx, ptr<ast::Name> name, bool silent, bool instantiate_generic) -> ptr<Node> {
  // Check for existance in-scope
  if (!ctx.scope->contains(name->text)) {
    if (!silent) Log::get().error(name->span, "unresolved name `{}`", name->text);
    return nullptr;
  }

  // Get the item from scope
  auto result = ctx.scope->get(name->text);

  // If we have a generic item; instantiate
  // TODO: Error checking here
  if (instantiate_generic) {
    if (isa<ir::Generic>(result)) {
      result = cast<ir::Generic>(result)->instantiate(
        ctx, name->type_arguments, name->span);
    } else if (name->type_arguments.size() > 0) {
      // We have type arguments but no generic
      if (!silent) {
        Log::get().error(name->span, "expected no type arguments, `{}` is not generic", name->text);
      }

      return nullptr;
    }
  }

  return result;
}

static bool generic_match(
  GContext& ctx,
  ptr<ir::Type> type,
  ptr<ast::Name> name,
  std::vector<ptr<ir::GenericTypeParameter>> type_parameters,
  std::unordered_map<std::string, ptr<ir::Type>>& result
) {
  if (!isa<ir::GenericInstantiation>(type)) {
    // Not instnatiated from a generic template

    // Only way this can match is if `name` is a single generic type
    // identifier

    for (auto& tp : type_parameters) {
      if (tp->name == name->text) {
        if (result.find(name->text) == result.end()) {
          result[name->text] = type;
        } else if (!result[name->text]->is_equal(type)) {
          return false;
        }

        return true;
      }
    }

    return false;
  }

  auto generic_i = cast<ir::GenericInstantiation>(type);

  ptr<ir::Scope> generic_scope;
  auto generic_impl = dynamic_cast<ir::GenericImplement*>(generic_i->base_generic);
  auto generic_rec = dynamic_cast<ir::GenericTypeRecord*>(generic_i->base_generic);

  if (generic_impl) {
    generic_scope = generic_impl->parent_scope;
  } else if (generic_rec) {
    generic_scope = generic_rec->parent_scope;
  }

  auto sb = ir::Scope::enter(generic_scope, ctx);

  auto target = ir::resolve_name(ctx, name, false, false);
  if (!target) return false;

  // Check for a match at base
  if (generic_i->base_generic != target.get()) return false;
  if (generic_i->type_arguments.size() != name->type_arguments.size()) return false;

  // Check for type arguments matches
  for (unsigned i = 0; i < generic_i->type_arguments.size(); ++i) {
    auto nta = name->type_arguments[i];

    if (isa<ast::TypeName>(nta)) {
      auto name = cast<ast::TypeName>(nta)->name;
      if (generic_match(
        ctx, generic_i->type_arguments[i], name, type_parameters, result)) {
        // Pass
        continue;
      }
    }

    auto name_a_t = pass::TypeBuild(ctx, true).run(name->type_arguments[i]);
    if (!name_a_t) return false;
    if (!name_a_t->is_equal(generic_i->type_arguments[i])) {
      return false;
    }
  }

  sb.exit();

  return true;
}

static ptr<ir::Node> resolve_implement(ptr<ir::Implement> impl, ptr<ast::Path> x, ptr<ir::Node> op) {
  auto fn = impl->scope->get<ir::Function>(x->member->text);
  if (fn) {
    // Do we have a self ?
    if (fn->has_self() && isa<ir::Value>(op)) {
      return make<ir::Method>(fn, cast<ir::Value>(op));
    } else {
      return fn;
    }
  }

  return nullptr;
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
  } else if (isa<ast::Path>(x->operand)) {
    op = resolve_path(ctx, cast<ast::Path>(x->operand), silent, build);
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

  if (op_t) {
    while (op_t->is_pointer()) {
      op_t = cast<ir::TypePointer>(op_t)->element;
      if (build) {
        op = make<ir::Indirect>(op->source, op_t, cast<ir::Value>(op));
      }
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
        ctx, x->member->type_arguments, x->span);
    }

    result = tmp;
  } else if (op_t != nullptr) {
    Match(*op_t) {
      Case(mch::C<ir::TypeRecord>()) {
        auto record = cast<ir::TypeRecord>(op_t);
        auto member_index = record->member_index_of(x->member->text);
        if (member_index >= 0) {
          result = make<ir::RecordMember>(x->member,
            record->members[member_index]->type, cast<ir::Value>(op),
            member_index);
        }
      } break;
    } EndMatch
  }

  if (!result && op_t) {
    // Check implementation registry
    for (auto& impl : ctx.impl[op_t.get()]) {
      result = resolve_implement(impl, x, op);
      if (result) break;
    }

    if (!result) {
      // Check generic implementation registry
      for (auto impl_g_it = ctx.impl_g.rbegin(); impl_g_it != ctx.impl_g.rend(); ++impl_g_it) {
        auto& impl_g = *impl_g_it;

        // Do we have the same number of type arguments
        auto const& impl = cast<ast::Implement>(impl_g->source);
        std::unordered_map<std::string, ptr<ir::Type>> result_t;
        if (generic_match(ctx, op_t, impl->target, impl_g->type_parameters, result_t)) {
          // Build type arguments to instantiate implementation
          std::vector<ptr<ir::Type>> type_a;
          for (auto type_param : impl_g->type_parameters) {
            type_a.push_back(result_t[type_param->name]);
          }

          // Instantiate Implementation
          auto impl_i = cast<ir::Implement>(impl_g->instantiate(ctx, type_a, x->span));
          result = resolve_implement(impl_i, x, op);
        }

        if (result) break;
      }
    }
  }

  if (!result && !silent) {
    Log::get().error(x->member->span, "`{}` has no member `{}`",
      op_t->name, x->member->text);
  }

  return result;
}
