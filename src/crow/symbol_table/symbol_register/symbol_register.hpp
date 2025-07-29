#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_HPP

// STL Includes:
#include <iomanip>
#include <memory>
#include <type_traits>
#include <unordered_map>

// Absolute Includes:
#include "crow/symbol_table/symbol_tree/symbol_tree.hpp"
#include "lib/stdexcept/stdexcept.hpp"

// TODO: Define a immutable interface for querying the symbol register.

namespace symbol_table::symbol_register {
// Forward Declarations:
template<typename T>
class SymbolRegister;

// Aliases:
template<typename T>
using SymbolRegisterPtr = std::shared_ptr<SymbolRegister<T>>;

// Classes:
/*!
 * The symbol register maps a @ref SymbolId to a concrete value.
 * This could be an AST node, or a MIR function or instruction.
 * It works by preallocating all pos
 */
template<typename T>
class SymbolRegister {
  private:
  using SymbolTreeId = symbol_tree::SymbolTreeId;

  //! We use a weak_ptr so we can catch if an item is expired.
  using SharedPtr = std::shared_ptr<T>;
  using WeakPtr = std::weak_ptr<T>;

  //! We need to keep track if a registery entry was never assigned.
  using ValueOpt = std::optional<WeakPtr>;
  using Register = std::unordered_map<SymbolTreeId, ValueOpt>;

  Register m_register;

  public:
  explicit SymbolRegister(const std::size_t t_size): m_register{}
  {
    // TODO: Optimize later, cause now we just reserve the full size.
    // Which is impractical, as we might not always need all of it.
    // This optimization, might need to be performed else where.

    m_register.reserve(t_size);
  }

  /*!
   * Retrieve the value associated with a
   * @param t_id Id to resolve, and obtain @ref SharedPtr from.
   *
   * @remark Throws on invalid value state.
   */
  auto get_value(const std::size_t t_id) -> SharedPtr
  {
    using lib::stdexcept::throw_invalid_argument;
    using lib::stdexcept::throw_unexpected_nullptr;

    const auto symbol_id_str{std::format(R"(for Symbol ID "{}")", t_id)};

    auto iter{m_register.find(t_id)};
    if(iter == m_register.end()) {
      const auto error_msg{std::format("No entry {}.", symbol_id_str)};

      throw_invalid_argument(error_msg);
    }

    // Check if the optional is uninitialized.
    auto& opt{iter->second};
    if(!opt) {
      // This should never happen, so we should throw.
      const auto error_msg{
        std::format("Uninitialized value {}.", symbol_id_str)};

      throw_invalid_argument(error_msg);
    }

    const auto& weak_ptr{opt.value()};
    if(!weak_ptr) {
      const auto error_msg{
        std::format("WeakPtr {} is nullptr.", symbol_id_str)};

      throw_unexpected_nullptr(error_msg);
    }

    // If the WeakPtr expired, then an architectural design mistake was made.
    // So we should throw and hopefully have this reported.
    if(weak_ptr.expired()) {
      const auto error_msg{
        std::format("Value {} is no longer in scope.", symbol_id_str)};

      throw_invalid_argument(error_msg);
    }

    // The SharedPtr is not allowed to be a nullptr either.
    const auto shared_ptr{weak_ptr.lock()};
    if(!shared_ptr) {
      const auto error_msg{
        std::format("SharedPtr {} is nullptr.", symbol_id_str)};

      throw_unexpected_nullptr(error_msg);
    }

    return {shared_ptr};
  }

  /*!
   * Insert into the registery.
   * @param t_id Symbol ID to associate value to.
   * @param t_value Value to insert.
   *
   * @remark Throws if there is already an entry for the given Symbol ID.
   */
  auto insert(const std::size_t t_id, const SharedPtr& t_value) -> void
  {
    using lib::stdexcept::throw_invalid_argument;

    auto& opt{m_register[t_id]};
    if(opt) {
      const auto error_msg{std::format(
        R"(Cant insert Symbol ID "{}" already has a value associated.)", t_id)};

      throw_invalid_argument(error_msg);
    }

    // Set register entry.
    opt = WeakPtr{t_value};
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
} // namespace symbol_table::symbol_register

#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_REGISTER_SYMBOL_REGISTER_HPP
