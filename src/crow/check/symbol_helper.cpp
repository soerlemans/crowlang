#include "symbol_helper.hpp"

// STL Includes:
#include <stdexcept>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"

namespace check {
// Methods:
auto SymbolHelper::get_symbol_data(NodePtr t_ptr) -> SymbolData
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

auto SymbolHelper::get_resolved_type(NodePtr t_ptr) -> SymbolData
{
  return get_symbol_data(t_ptr).resolve_type();
}

auto SymbolHelper::get_native_type(NodePtr t_ptr) -> NativeTypeOpt
{
  return get_symbol_data(t_ptr).native_type();
}

auto SymbolHelper::get_type_list(NodeListPtr t_list) -> SymbolDataList
{
  SymbolDataList list;

  for(const auto& ptr : *t_list) {
    list.push_back(get_symbol_data(ptr));
  }

  return list;
}

auto SymbolHelper::get_resolved_type_list(NodeListPtr t_list) -> SymbolDataList
{
  SymbolDataList list;

  for(const auto& ptr : *t_list) {
    list.push_back(get_resolved_type(ptr));
  }

  return list;
}
} // namespace check
