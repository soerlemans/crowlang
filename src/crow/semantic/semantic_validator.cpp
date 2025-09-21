#include "semantic_validator.hpp"

// Absolute Includes:
#include "crow/debug/debug.hpp"
#include "crow/diagnostic/diagnostic.hpp"

namespace semantic {
// Using:
using diagnostic::throw_type_error;

// TODO: Implement.
auto SemanticValidator::promote(const SymbolData& t_lhs,
                                const SymbolData& t_rhs,
                                const TypeOperandPriority t_enforce) const
  -> NativeTypeOpt
{
  NativeTypeOpt opt{};

  const auto lhs{t_lhs.native_type()};
  const auto rhs{t_rhs.native_type()};

  // FIXME: For now we must ensure both types are native types to consider
  // promotion.
  if(lhs && rhs) {
    opt = m_type_promoter.promote(lhs.value(), rhs.value(), t_enforce);
  }

  return opt;
}

auto SemanticValidator::validate_arithmetic(const BinaryOperation& t_binop)
  -> SymbolData
{
  const auto& [lhs, rhs, pos] = t_binop;

  DBG_INFO("Arithmetic: lhs: ", lhs, " rhs: ", rhs);

  // FIXME: Copy preemptively from lhs now.
  SymbolData ret{lhs};

  const auto opt{promote(lhs, rhs)};
  if(opt) {
    ret = opt.value();
  } else if(lhs != rhs) {
    std::stringstream ss;

    DBG_ERROR("Typeof: ", lhs, " != ", rhs);

    ss << "Arithmetic operation contains a type mismatch.\n";
    ss << "typeof lhs = " << lhs << "\n";
    ss << "typeof rhs = " << rhs << "\n\n";

    ss << pos;

    throw_type_error(ss.str());
  }

  DBG_INFO("Arithmetic: result: ", ret);

  return ret;
}

auto SemanticValidator::validate_comparison(const BinaryOperation& t_binop)
  -> SymbolData
{
  const auto& [lhs, rhs, pos] = t_binop;

  DBG_INFO("Comparison: lhs: ", lhs, " rhs: ", rhs);

  const auto opt{promote(lhs, rhs)};

  // If promotion fails and the types are not equal.
  // We have a type mismatch.
  if(!opt && lhs != rhs) {
    std::stringstream ss{};

    ss << "Comparison operation contains a type mismatch.\n";
    ss << "typeof lhs = " << lhs << "\n";
    ss << "typeof rhs = " << rhs << "\n\n";

    ss << pos;

    throw_type_error(ss.str());
  }

  return SymbolData{NativeType::BOOL};
}
} // namespace semantic
