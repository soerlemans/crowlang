#ifndef SYMBOL_REGISTER_BUILDER_INTERFACE_HPP
#define SYMBOL_REGISTER_BUILDER_INTERFACE_HPP

namespace symbol_table {
class SymbolRegisterBuilderInterface {
  private:
  public:
  SymbolRegisterBuilder() = default;

  virtual auto on_function() -> void;
  virtual auto on_struct() -> void;

  virtual auto on_variable_ref() -> void;
  virtual auto on_variable_init() -> void;

  virtual ~SymbolRegisterBuilder() = default;
};
} // namespace symbol_table

#endif // SYMBOL_REGISTER_BUILDER_INTERFACE_HPP
