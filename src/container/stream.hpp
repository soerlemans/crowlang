#ifndef NEWLANG_CONTAINER_STREAM_HPP
#define NEWLANG_CONTAINER_STREAM_HPP

// STL Includes:
#include <concepts>
#include <iterator>


namespace container {
// Classes:
/*! Streams are containers that keep track of their current element.
 */
template<typename T>
requires std::bidirectional_iterator<typename T::iterator>
class Stream : public T {
  private:
  using Iterator = typename T::iterator;
  using Value = typename T::value_type;

  Iterator m_iter;

  public:
  Stream(): m_iter{this->begin()}
  {}

  Stream(const Stream& t_stream): T{t_stream}, m_iter{this->begin()}
  {}

  Stream(Stream&& t_stream): T{std::move(t_stream)}, m_iter{this->begin()}
  {}

  virtual auto next() -> Value&
  {
    auto iter{m_iter};
    m_iter++;

    return *iter;
  }

  virtual auto prev() -> Value&
  {
    auto iter{m_iter};
    m_iter--;

    return *iter;
  }

  virtual auto current() const -> Value&
  {
    return *m_iter;
  }

  virtual auto eos() const -> bool
  {
    return m_iter == this->end();
  }

  virtual ~Stream() = default;
};
} // namespace container

#endif // NEWLANG_CONTAINER_STREAM_HPP
