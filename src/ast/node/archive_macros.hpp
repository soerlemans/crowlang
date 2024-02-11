#ifndef ARCHIVE_MACROS_HPP
#define ARCHIVE_MACROS_HPP

/*!
 * @file
 *
 * Header dedicated to.
 */

// Macros:
// TODO: Move these cereal related macros somewhere else?
/*!
 * Make it so that only cereal has access to the default constructor.
 * Most node types should not be default constructible.
 */
#define GIVE_ARCHIVE_ACCESS(t_type) \
  protected:                        \
  t_type() = default;               \
                                    \
  friend cereal::access

//!
#define DEFINE_SERIALIZE_METHOD() \
  template<typename Archive>      \
  auto serialize([[maybe_unused]] Archive& t_archive)->void

//!
#define DEFINE_SERIALIZE_METHOD_NIL() \
  DEFINE_SERIALIZE_METHOD()           \
  {}

//! Macro for making a type serializable by the cereal library.
#define MAKE_ARCHIVEABLE(t_type) \
  GIVE_ARCHIVE_ACCESS(t_type);   \
                                 \
  public:                        \
  DEFINE_SERIALIZE_METHOD()

//! Macro for easily archiving nodes dependent on traits.
#define MAKE_TRAITS_ARCHIVEABLE(t_type, ...)                       \
  MAKE_ARCHIVEABLE(t_type)                                         \
  {                                                                \
    archive_traits<Archive, t_type, __VA_ARGS__>(t_archive, this); \
  }

//!
#define REGISTER_ARCHIVEABLE_TYPE(t_namespace, t_type)           \
  CEREAL_REGISTER_POLYMORPHIC_RELATION(ast::node::NodeInterface, \
                                       t_namespace::t_type);     \
  CEREAL_REGISTER_TYPE_WITH_NAME(t_namespace::t_type, #t_type)


#endif // ARCHIVE_MACROS_HPP
