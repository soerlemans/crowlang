#ifndef CROW_CROW_CONTAINER_STREAM_HPP
#define CROW_CROW_CONTAINER_STREAM_HPP

// STL Includes:
#include <concepts>
#include <iterator>
#include <optional>

namespace container {
// Classes:
/*!
 * Streams are containers that keep track of their current element.
 */
template<typename T>
  requires std::bidirectional_iterator<typename T::iterator>
class Stream : public T {
  private:
  using Iterator = typename T::iterator;
  using Value = typename T::value_type;
  using ValueOpt = std::optional<Value>;

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
    m_iter++;

    return *m_iter;
  }

  virtual auto prev() -> Value&
  {
    m_iter--;

    return *m_iter;
  }

  virtual auto peek() const -> ValueOpt
  {
    ValueOpt opt;
    auto iter{m_iter};

    iter++;
    if(iter != this->end()) {
      opt = *iter;
    }

    return opt;
  }

  virtual auto iter() const -> Iterator
  {
    return m_iter;
  }

  virtual auto set(const Iterator t_iter) -> void
  {
    m_iter = std::move(t_iter);
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

#endif // CROW_CROW_CONTAINER_STREAM_HPP
