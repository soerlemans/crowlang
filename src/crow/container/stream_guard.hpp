#ifndef CROW_CROW_CONTAINER_STREAM_GUARD_HPP
#define CROW_CROW_CONTAINER_STREAM_GUARD_HPP

// STL Includes:
#include <functional>

// Local Includes:
#include "stream.hpp"

namespace container {
// Classes:
/*!
 * Class that protects the state of a stream.
 * Perform a check if a
 */
template<typename T>
class StreamGuard {
  private:
  using StreamType = Stream<T>;
  using Iterator = StreamType::iterator;
  using Function = std::function<bool()>;

  StreamType& m_stream;
  Iterator m_saved;
  Function m_check;

  public:
  StreamGuard(Stream<T>& t_stream, Function&& t_check)
    : m_stream{t_stream}, m_saved{m_stream.iter()}, m_check{t_check}
  {}

  /*!
   * Restore from the @ref m_saved iterator.
   */
  auto restore() -> void
  {
    m_stream.set(m_saved);
  }

  virtual ~StreamGuard()
  {
    // Check passed function to check if we should restore from the point.
    if(m_check()) {
      restore();
    }
  }
};

} // namespace container

#endif // CROW_CROW_CONTAINER_STREAM_GUARD_HPP
