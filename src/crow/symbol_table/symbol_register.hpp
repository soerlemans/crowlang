#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_HPP

// STL Includes:
#include <memory>
#include <type_traits>
#include <unordered_map>

// Absolute Includes:
#include "crow/symbol_table/symbol_table.hpp"
#include "lib/stdexcept/stdexcept.hpp"

namespace symbol_table {
// Forward declarations:
enum class SymbolRegisterError;

// Aliases:
template<typename T>
using SymbolRegisterResult = std::expected<T, SymbolRegisterError>;

// Enums:
enum class SymbolRegisterError {
  UNINITIALIZED_ITEM,
}

// Classes:
/*!
 * The symbol register maps a @ref SymbolId to a concrete value.
 * This could be an AST node, or a MIR function or instruction.
 * It works by preallocating all pos
 */
template<typename T>
class SymbolRegister {
  private:
  //! We use a weak_ptr so we can catch if an item is expired.
  using SharedPtr = std::shared_ptr<T>;
  using WeakPtr = std::weak_ptr<T>;

  //! We need to keep track if a registery entry was never assigned.
  using DataOpt = std::optional<WeakPtr>;
  using Register = std::unordered_map<SymbolTableId, DataOpt>;

  Register m_register;

  public:
  explicit SymbolRegister(const std::size_t t_size): m_register{}
  {
    // TODO: Optimize later, cause now we just reserve the full size.
    // Which is impractical, as we might not always need all of it.
    // This optimization, might need to be performed else where.

    m_register.reserve(t_size);
  }

  auto retrieve(const std::size_t t_id) -> SharedPtr
  {
    using lib::stdexcept::throw_invalid_argument;

    const auto quoted_id{t_id};

    auto iter{m_register.find(t_id)};
    if(iter == m_register.end()) {
      const auto error_msg{
        std::format("No entry for Symbol ID {}.", quoted_id)};

      throw_invalid_argument(error_msg);
    }

    // Check if the optional is uninitialized.
    auto& opt{iter->second};
    if(!opt) {
      // This should never happen, so we should throw.
      const auto error_msg{
        std::format("Uninitialized entry for Symbol ID {}.", quoted_id)};

      throw_invalid_argument(error_msg);
    }

    // If the WeakPtr expired, then an architectural mistake was made.
    // So we should also throw.
    const auto& weak_ptr{opt.value()};
    if(weak_ptr.expired()) {
      const auto error_msg{std::format(
        "Entry for Symbol ID {} is no longer in scope.", quoted_id)};

      throw_invalid_argument(error_msg);
    }

    return {weak_ptr.lock()};
  }

  auto insert_at(const std::size_t t_id, const SharedPtr& t_item) -> void
  {
    using lib::stdexcept::throw_invalid_argument;

    auto& opt{m_register[t_id]};
    if(opt) {
      const auto quoted_id{std::quoted(id)};
      const auto error_msg{std::format(
        "Cant insert Symbol ID {} already has an item associated.", quoted_id)};

      throw_invalid_argument(error_msg);
    }

    // Set register entry.
    opt = WeakPtr{t_item};
  }

  auto begin() -> Register::iterator
  {
    return m_register.begin();
  }

  auto end() -> Register::iterator
  {
    return m_register.end();
  }

  auto size() -> std::size_t
  {
    return m_register.size();
  }

  virtual ~SymbolRegister() = default;
};
} // namespace symbol_table

#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_HPP
