#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_PASS_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_PASS_HPP

// Local Includes:
#include "symbol_register.hpp"

namespace symbol_table::symbol_register {
template<typename RegisterType>
class SymbolRegisterPass {
  protected:
  using Register = SymbolRegister<RegisterType>;
  using EntrypType = Register::EntryType;

  public:
  SymbolRegisterPass() = default;

  virtual auto on_entry(EntryType& t_entry) -> void = 0;

  virtual auto run_pass(Register& t_register) -> void
  {
    for(auto& entry : t_register) {
      on_entry(entry);
    }
  }

  virtual ~SymbolRegisterPass() = default;
};
} // namespace symbol_table::symbol_register

#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_PASS_HPP
