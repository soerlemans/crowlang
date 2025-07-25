#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_HPP

namespace symbol_table {
/*!
 * The symbol register maps a @ref SymbolId to a concrete value.
 */
template<typename T>
class SymbolRegister {
  private:
  public:
  SymbolRegister() = default;

  virtual ~SymbolRegister() = default;
};

} // namespace symbol_table

#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_HPP
