#ifndef CROW_CROW_SEMANTIC_ANNOTATION_QUEUE_HPP
#define CROW_CROW_SEMANTIC_ANNOTATION_QUEUE_HPP

// STL Includes:
#include <queue>

// Absolute includes:
#include "crow/ast/node/node_traits/type_data.hpp"
#include "crow/types/semantic/semantic.hpp"
#include "crow/types/semantic/symbol.hpp"

namespace semantic {
// Using:
namespace node = ast::node;

using node::node_traits::TypeData;
using types::symbol::SymbolData;

// Structs:
/*!
 * Contains the job info for where the type info.
 * Needs to be written to in the AST.
 */
struct AnnotationInfo {
  TypeData* m_node;
  SymbolData m_data;
};

// Classes:
class AnnotationQueue {
  private:
  std::queue<AnnotationInfo> m_annot_queue;

  public:
  //! Push type annotation
  auto push(AnnotationInfo t_info) -> void;

  //! Process the queue and annotate the AST.
  auto annotate_ast() -> void;

  virtual ~AnnotationQueue() = default;
};
} // namespace semantic

#endif // CROW_CROW_SEMANTIC_ANNOTATION_QUEUE_HPP
