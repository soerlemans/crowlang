#include "semantic_checker_helper.hpp"

// STL Includes:
#include <stdexcept>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"

namespace check {
// Using Statements:
using exception::type_error;

// Methods:
// Environment state related methods:
auto SemanticCheckerHelper::add_symbol(const std::string_view t_id,
                                       const SymbolData& t_data) -> void
{
  m_env.add_symbol({std::string{t_id}, t_data});
  // m_symbol_table.insert();
}

auto SemanticCheckerHelper::get_symbol(const std::string_view t_id) const
  -> SymbolData
{
  return m_env.get_symbol(t_id);
}

auto SemanticCheckerHelper::push_env() -> void
{
  m_env.push_env();
}

auto SemanticCheckerHelper::pop_env() -> void
{
  m_env.pop_env();
}

auto SemanticCheckerHelper::clear_env() -> void
{
  m_env.clear();
}

// Type promotion related methods:
auto SemanticCheckerHelper::handle_condition(const SymbolData& t_data,
                                             const TextPosition& t_pos) const
  -> void
{
  std::stringstream ss;

  if(const auto opt{t_data.native_type()}; opt) {
    if(!is_condition(opt.value())) {
      ss << "Expected a pointer, integer or a boolean for a conditional "
         << "expression.\n\n";

      ss << t_pos;

      type_error(ss.str());
    }
  } else {
    ss << "Non native types can not casted to " << std::quoted("bool")
       << ".\n\n";

    ss << t_pos;

    type_error(ss.str());
  }
}

auto SemanticCheckerHelper::promote(const SymbolData& t_lhs,
                                    const SymbolData& t_rhs,
                                    const bool enforce_lhs) const
  -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto lhs{t_lhs.native_type()};
  const auto rhs{t_rhs.native_type()};

  if(lhs && rhs) {
    opt = m_type_promoter.promote(lhs.value(), rhs.value(), enforce_lhs);
  }

  return opt;
}

auto SemanticCheckerHelper::get_symbol_data(NodePtr t_ptr) -> SymbolData
{
  SymbolData data;

  const auto any{traverse(t_ptr)};
  if(any.has_value()) {
    try {
      data = std::any_cast<SymbolData>(any);
    } catch(const std::bad_any_cast& e) {
      DBG_CRITICAL(e.what());

      // TODO: Print elegant error message and terminate
      throw e;
    }
  }

  return data;
}

auto SemanticCheckerHelper::get_resolved_type(NodePtr t_ptr) -> SymbolData
{
  return get_symbol_data(t_ptr).resolve_type();
}

auto SemanticCheckerHelper::get_native_type(NodePtr t_ptr) -> NativeTypeOpt
{
  return get_symbol_data(t_ptr).native_type();
}

auto SemanticCheckerHelper::get_type_list(NodeListPtr t_list) -> SymbolDataList
{
  SymbolDataList list;

  for(const auto& ptr : *t_list) {
    list.push_back(get_symbol_data(ptr));
  }

  return list;
}

auto SemanticCheckerHelper::get_resolved_type_list(NodeListPtr t_list)
  -> SymbolDataList
{
  SymbolDataList list;

  for(const auto& ptr : *t_list) {
    list.push_back(get_resolved_type(ptr));
  }

  return list;
}
} // namespace check
