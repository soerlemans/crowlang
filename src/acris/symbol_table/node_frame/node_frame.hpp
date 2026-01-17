#ifndef ACRIS_ACRIS_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_HPP
#define ACRIS_ACRIS_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_HPP

// Absolute includes:
#include "acris/ast/node/include.hpp"
#include "acris/ast/visitor/node_visitor.hpp"
#include "acris/symbol_table/symbol_table.hpp"

namespace symbol_table::node_frame {
// Using Declarations:
using ast::node::NodeInterface;
using symbol_register::SymbolRegister;
using symbol_register::SymbolRegisterPtr;

// Aliases:
/*!
 * Different specializiations of @ref SymbolTable are usually, constructed.
 * From the AST, this is a frame/view which maps the @ref SymbolTree.
 * To accompanying AST nodes.
 */
using NodeFrame = SymbolTable<NodeInterface>;
using NodeFramePtr = SymbolTablePtr<NodeInterface>;

using NodeRegister = SymbolRegister<NodeInterface>;

} // namespace symbol_table::node_frame

#endif // ACRIS_ACRIS_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_HPP
