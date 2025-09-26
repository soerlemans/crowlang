#include "semantic_validator.hpp"

// Absolute Includes:
#include "crow/debug/debug.hpp"
#include "crow/diagnostic/diagnostic.hpp"

namespace semantic {
// Using:
using diagnostic::throw_type_error;

auto SemanticValidator::add_symbol_declaration(const std::string_view t_key,
                                               const SymbolData& t_data) -> void
{
  // First check if the entry exists.
  const auto [iter, exists] = m_symbol_state.find(t_key);
  if(exists) {
    const auto& symbol{iter->second};

    std::stringstream ss{};
    switch(symbol.m_status) {
      case SymbolStatus::DECLARED:
        [[fallthrough]];
      case SymbolStatus::DEFINED: {
        // Check for conflicting.
        if(t_data != symbol.m_data) {
          ss << "Conflicting declarations and definitions for "
             << std::quoted(t_key) << ".";

          throw_type_error(ss.str());
        }
        break;
      }

      default: {
        using lib::stdexcept::throw_invalid_argument;

        throw_invalid_argument("Unhandled SymbolStatus case.");
        break;
      }
    }
  } else {
    Symbol symbol{SymbolStatus::DECLARED, t_data};
    m_symbol_state.insert({std::string{t_key}, symbol});
  }
}

auto SemanticValidator::add_symbol_definition(const std::string_view t_key,
                                              const SymbolData& t_data) -> void
{
  // First check if the entry exists.
  const auto [iter, exists] = m_symbol_state.find(t_key);
  if(exists) {
    auto& symbol{iter->second};

    std::stringstream ss{};
    switch(symbol.m_status) {
      case SymbolStatus::DECLARED: {
        // Check symbolData equality.
        if(t_data == symbol.m_data) {
          // Change from declaration to definition.
          symbol.m_status = SymbolStatus::DEFINED;
        } else {
          ss << "Conflicting declaration and definition for "
             << std::quoted(t_key) << ".";

          throw_type_error(ss.str());
        }
        break;
      }

      case SymbolStatus::DEFINED: {
        // Redefinition is not allowed so throw.
        ss << "Redefining " << std::quoted(t_key) << " is not allowed.";

        throw_type_error(ss.str());
        break;
      }

      default: {
        using lib::stdexcept::throw_invalid_argument;

        throw_invalid_argument("Unhandled SymbolStatus case.");
        break;
      }
    }
  } else {
    Symbol symbol{SymbolStatus::DEFINED, t_data};
    m_symbol_state.insert({std::string{t_key}, symbol});
  }
}

auto SemanticValidator::get_symbol_data_from_env(
  const std::string_view t_key) const -> SymbolData
{
  return m_symbol_state.get_data(t_key);
}

auto SemanticValidator::handle_condition(const SymbolData& t_data,
                                         const TextPosition& t_pos) const
  -> void
{
  std::stringstream ss{};

  if(const auto opt{t_data.native_type()}; opt) {
    if(!is_condition(opt.value())) {
      ss << "Expected a pointer, integer or a boolean for a conditional "
         << "expression.\n\n";

      ss << t_pos;

      throw_type_error(ss.str());
    }
  } else {
    ss << "Non native types can not casted to " << std::quoted("bool")
       << ".\n\n";

    ss << t_pos;

    throw_type_error(ss.str());
  }
}

// TODO: Implement.
auto SemanticValidator::promote(const SymbolData& t_lhs,
                                const SymbolData& t_rhs,
                                const PromotionMode t_mode) const
  -> NativeTypeOpt
{
  NativeTypeOpt opt{};

  const auto lhs{t_lhs.native_type()};
  const auto rhs{t_rhs.native_type()};

  // FIXME: For now we must ensure both types are native types to consider
  // promotion.
  if(lhs && rhs) {
    opt = m_type_promoter.promote(lhs.value(), rhs.value(), t_mode);
  }

  return opt;
}

auto SemanticValidator::validate_logical_unop(const UnaryOperationData& t_data)
  -> SymbolData
{
  const auto& [lhs, pos] = t_data;

  // Check if the operand is convertible to a boolean.
  handle_condition(lhs, pos);

  return SymbolData{NativeType::BOOL};
}

auto SemanticValidator::validate_logical_binop(
  const BinaryOperationData& t_data) -> SymbolData
{
  const auto& [lhs, rhs, pos] = t_data;

  // Check if both operands can be converted to a boolean.
  handle_condition(lhs, pos);
  handle_condition(rhs, pos);

  return SymbolData{NativeType::BOOL};
}

auto SemanticValidator::validate_arithmetic(const BinaryOperationData& t_data)
  -> SymbolData
{
  const auto& [lhs, rhs, pos] = t_data;

  DBG_INFO("Arithmetic: lhs: ", lhs, " rhs: ", rhs);

  // FIXME: Copy preemptively from lhs now.
  SymbolData ret{lhs};

  const auto opt{promote(lhs, rhs, PromotionMode::PEAK)};
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

auto SemanticValidator::validate_assignment(const BinaryOperationData& t_data)
  -> SymbolData
{
  auto [lhs, expr, pos] = t_data;

  // We need to resolve to the underlying type of the variable.
  // For type validation purposes.
  const auto var_resolved{lhs.resolve_type()};

  std::stringstream ss{};

  if(lhs.is_const()) {
    ss << "Reassigning a const variable is illegal.\n\n";

    ss << "<lhs> = <expr>\n";
    ss << "typeof lhs = " << lhs << "\n";
    ss << "typeof expr = " << expr << "\n\n";

    ss << pos;

    throw_type_error(ss.str());
  }

  // The right hand side must be promoteable or castable to the left hand side.
  // We dont care about the value, only if it is promoteable.
  const auto opt{promote(lhs, expr, PromotionMode::PROMOTE_TO_LHS)};
  if(!opt && var_resolved != expr) {
    ss << "Types do not match on assignment.\n\n";

    ss << "<lhs> = <expr>\n";
    ss << "typeof lhs = " << lhs << "\n";
    ss << "typeof expr = " << expr << "\n\n";

    ss << pos;

    throw_type_error(ss.str());
  }

  return lhs;
}

auto SemanticValidator::validate_comparison(const BinaryOperationData& t_data)
  -> SymbolData
{
  const auto& [lhs, rhs, pos] = t_data;

  // We only check if the promotion is possible because we dont use the result.
  const auto opt{promote(lhs, rhs, PromotionMode::PEAK)};

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
