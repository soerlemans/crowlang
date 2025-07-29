#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_BUILDER_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_BUILDER_HPP

namespace symbol_table {
/*!
 * This is a base class for constructing a @ref SymbolRegistery.
 * It is
 */
template<typename T>
class SymbolRegisterBuilder {
  private:
  public:
  SymbolRegisterBuilder() = default;

  // auto retrieve_symbol_register() -> SymbolRegisterPtr
  // {}

  virtual ~SymbolRegisterBuilder() = default;
};
} // namespace symbol_table

#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_BUILDER_HPP
