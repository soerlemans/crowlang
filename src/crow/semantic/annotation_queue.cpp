#include "annotation_queue.hpp"

namespace semantic {
auto AnnotationQueue::push(AnnotationInfo t_info) -> void
{
  // Process later so that we can freely edit type info after the fact.
  // This is necessary for methods which change the original type.
  // Like a Method adding a method to the type definition.
  // After the initial type defintion of the struct.

  // The moment we convert to a TypeVariant.
  // We create a new shared_ptr and cant update it anymore.
  // If we delay this after traversal it works properly.

  m_annot_queue.push(std::move(t_info));
}

auto AnnotationQueue::annotate_ast() -> void
{
  while(!m_annot_queue.empty()) {
    auto& [node, data] = m_annot_queue.front();
    // Convert SymbolData to TypeVariant.
    const auto type_variant{data.type_variant()};

    // Annotate AST, with TypeVariant.
    node->set_type(type_variant);

    m_annot_queue.pop();
  }
}

} // namespace semantic
