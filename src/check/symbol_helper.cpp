#include "symbol_helper.hpp"

// STL Includes:
#include <stdexcept>

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"


// Using Statements:
using namespace check;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto SymbolHelper::get_symbol_data(NodePtr t_ptr) -> SymbolData
{
  SymbolData variant;

  auto any{traverse(t_ptr)};
  if(any.has_value()) {
    try {
      variant = std::any_cast<SymbolData>(any);
    } catch(const std::bad_any_cast& e) {
      DBG_CRITICAL(e.what());

      // TODO: Print elegant error message and terminate
      throw e;
    }
  }

  return variant;
}

auto SymbolHelper::get_type_list(NodeListPtr t_list) -> TypeList
{
  TypeList list;

  for(const auto& ptr : *t_list) {
    list.push_back(get_symbol_data(ptr));
  }

  return list;
}
