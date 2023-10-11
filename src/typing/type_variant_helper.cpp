#include "type_variant_helper.hpp"

// STL Includes:
#include <stdexcept>

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"


// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto TypeVariantHelper::get_variant(NodePtr t_ptr) -> TypeVariant
{
  TypeVariant variant;

  auto any{traverse(t_ptr)};
  if(any.has_value()) {
    try {
      variant = std::any_cast<TypeVariant>(any);
    } catch(const std::bad_any_cast& e) {
      DBG_CRITICAL(e.what());

      // TODO: Print elegant error message and terminate
      throw e;
    }
  }

  return variant;
}

auto TypeVariantHelper::get_list(NodeListPtr t_list) -> TypeVec
{
  TypeVec vec;

  for(auto& ptr : *t_list) {
    vec.push_back(get_variant(ptr));
  }

  return vec;
}
