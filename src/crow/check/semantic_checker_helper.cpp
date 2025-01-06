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
                                       const SymbolData& t_data) -> bool
{
  // If insertion in the environment fails, something is going wrong.
  // Possibly a duplicate entry or similar.
  const auto [iter, insertion_success] =
    m_env_state.add_symbol({std::string{t_id}, t_data});


  DBG_VERBOSE("EnvState: ", m_env_state);

  // Add symbol to global symbol table.
  // Do not insert if insertion in environment failed.
  if(insertion_success) {
    m_symbol_table_factory.add_symbol(t_id, t_data);
  }

  return insertion_success;
}

auto SemanticCheckerHelper::get_symbol(const std::string_view t_id) const
  -> SymbolData
{
  return m_env_state.get_symbol(t_id);
}

auto SemanticCheckerHelper::retrieve_symbol_table() const -> SymbolTablePtr
{
  // Retrieve the construct global symbol table.
  return m_symbol_table_factory.retrieve();
}

auto SemanticCheckerHelper::push_env() -> void
{
  m_env_state.push_env();
  m_symbol_table_factory.push_scope();
}

auto SemanticCheckerHelper::pop_env() -> void
{
  m_env_state.pop_env();
  m_symbol_table_factory.pop_scope();
}

auto SemanticCheckerHelper::clear_env() -> void
{
  // Reset/clear the construction object.
  m_env_state.clear();
  m_symbol_table_factory.clear();
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
