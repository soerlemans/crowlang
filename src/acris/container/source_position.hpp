#ifndef ACRIS_ACRIS_CONTAINER_SOURCE_POSITION_HPP
#define ACRIS_ACRIS_CONTAINER_SOURCE_POSITION_HPP

// STL Includes:
#include <string>
#include <string_view>

namespace container {
/*!
 * Structure contains data of a position Acris's source code.
 */
struct SourcePosition {
  // Members:
  std::string m_source;
  std::size_t m_line_nr;
  std::string m_function;

  SourcePosition(std::string_view t_source, std::size_t t_line_nr,
                 std::string_view t_function);

  friend auto operator<<(std::ostream& t_os, const SourcePosition& t_sp)
    -> std::ostream&;

  virtual ~SourcePosition() = default;
};
} // namespace container

#endif // ACRIS_ACRIS_CONTAINER_SOURCE_POSITION_HPP
