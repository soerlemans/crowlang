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

auto SemanticValidator::validate_arithmetic(const BinaryOperationData& t_data)
  -> SymbolData
{
  const auto& [lhs, rhs, pos] = t_data;

  DBG_INFO("Arithmetic: lhs: ", lhs, " rhs: ", rhs);

  // FIXME: Copy preemptively from lhs now.
  SymbolData ret{lhs};

  const auto opt{promote(lhs, rhs, TypeOperandPriority::PEAK)};
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
  return SymbolData{NativeType::BOOL};
}

auto SemanticValidator::validate_comparison(const BinaryOperationData& t_data)
  -> SymbolData
{
  const auto& [lhs, rhs, pos] = t_data;

  DBG_INFO("Comparison: lhs: ", lhs, " rhs: ", rhs);

  const auto opt{promote(lhs, rhs, TypeOperandPriority::PEAK)};

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
