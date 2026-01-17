#ifndef ACRIS_LIB_IOMANIP_COND_NL_HPP
#define ACRIS_LIB_IOMANIP_COND_NL_HPP

// STL Includes:
#include <iosfwd>

namespace lib::iomanip {
/*!
 * Conditional newline insertion class.
 */
class CondNl {
  private:
  static bool m_insert_nl;

  public:
  CondNl() = default;

  // Globally enable/disable the conditional newlines.
  static auto enable() -> void;
  static auto disable() -> void;

  // Friend functions:
  friend auto operator<<(std::ostream& t_os, CondNl t_cond_nl) -> std::ostream&;

  virtual ~CondNl() = default;
};

// Functions:
auto cond_nl(std::ostream& t_os) -> std::ostream&;
} // namespace lib::iomanip


#endif // ACRIS_LIB_IOMANIP_COND_NL_HPP
