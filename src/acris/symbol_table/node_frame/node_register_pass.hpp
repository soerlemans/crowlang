#ifndef ACRIS_ACRIS_SYMBOL_TABLE_NODE_FRAME_NODE_REGISTER_PASS_HPP
#define ACRIS_ACRIS_SYMBOL_TABLE_NODE_FRAME_NODE_REGISTER_PASS_HPP

// Absolute includes:
#include "acris/symbol_table/symbol_register/symbol_register_pass.hpp"

// Local includes:
#include "node_frame.hpp"

namespace symbol_table::node_frame {
// Using Declarations:
using symbol_register::SymbolRegisterPass;

// Classes:
template<typename RegisterType>
class NodeRegisterPass : public SymbolRegisterPass<NodeInterface> {
  public:
  NodeRegisterPass() = default;

  virtual auto on_parameter(ast::node::function::Parameter* t_param)
    -> void = 0;
  virtual auto on_function(ast::node::function::Function* t_fn) -> void = 0;
  virtual auto on_let(ast::node::lvalue::Let* t_let) -> void = 0;
  virtual auto on_var(ast::node::lvalue::Var* t_var) -> void = 0;

  auto on_entry(EntryType& t_entry) -> void override
  {
    using ast::node::function::Function;
    using ast::node::function::Parameter;
    using ast::node::lvalue::Let;
    using ast::node::lvalue::Var;

    const auto& [symbol_id, node] = t_entry;

    if(auto ptr{std::dynamic_pointer_cast<Parameter>(node)}; ptr) {
      auto* raw_ptr{ptr.get()};

      on_parameter(raw_ptr);
    } else if(auto ptr{std::dynamic_pointer_cast<Function>(node)}; ptr) {
      auto* raw_ptr{ptr.get()};

      on_function(raw_ptr);
    } else if(auto ptr{std::dynamic_pointer_cast<Let>(node)}; ptr) {
      auto* raw_ptr{ptr.get()};

      on_let(raw_ptr);
    } else if(auto ptr{std::dynamic_pointer_cast<Var>(node)}; ptr) {
      auto* raw_ptr{ptr.get()};

      on_var(raw_ptr);
    } else {
      // TODO: Throw, unexpected state.
    }
  };

  virtual ~NodeRegisterPass() = default;
};

} // namespace symbol_table::node_frame

#endif // ACRIS_ACRIS_SYMBOL_TABLE_NODE_FRAME_NODE_REGISTER_PASS_HPP
