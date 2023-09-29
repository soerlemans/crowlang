#ifndef BIMAP_HPP
#define BIMAP_HPP

// STL Includes:
#include <initializer_list>

// Library Includes:
#include <boost/bimap.hpp>


namespace container {
template<typename Key, typename Value>
class BiMap : public boost::bimap<Key, Value> {
  public:
  BiMap(const std::initializer_list<std::pair<Key, Value>> t_init)
    : boost::bimap<Key, Value>{t_init.begin(), t_init.end()}
  {}

  virtual ~BiMap() = default;
};
} // namespace container

#endif // BIMAP_HPP