#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_PASS_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_PASS_HPP

// Local Includes:
#include "symbol_register.hpp"

namespace symbol_table::symbol_register {
template<typename RegisterType, typename ResultType = void>
class SymbolRegisterPass {
  protected:
  using Register = SymbolRegister<RegisterType>;
  using EntrypType = Register::EntryType;

  public:
  SymbolRegisterPass() = default;

  virtual auto process_entry(EntryType& t_entry) -> void = 0;

  virtual auto process(Register& t_register) -> void
  {
    for(auto& entry : t_register) {
      process_entry(entry);
    }
  }

  virtual auto run(Register& t_register) -> ResultType = 0;

  virtual ~SymbolRegisterPass() = default;
};
} // namespace symbol_table::symbol_register

#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_PASS_HPP
