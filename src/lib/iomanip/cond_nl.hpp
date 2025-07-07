#ifndef COND_NL_HPP
#define COND_NL_HPP

namespace lib::iomanip {
/*!
 * Conditional newline insertion class.
 */
class CondNl {
  private:
  static bool m_insert_nl;

  public:
  CondNl() = default;

  virtual ~CondNl() = default;
};

} // namespace lib::iomanip

#endif // COND_NL_HPP
