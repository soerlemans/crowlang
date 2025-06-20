#ifndef CROW_CROW_AST_ARCHIVE_ARCHIVE_HPP
#define CROW_CROW_AST_ARCHIVE_ARCHIVE_HPP

/*!
 * @file
 *
 * Header dedicated to.
 */

// Library Includes:
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/optional.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/vector.hpp>


// Macros:
// TODO: Move these cereal related macros somewhere else?
/*!
 * Make it so that only cereal has access to the default constructor.
 * Most node types should not be default constructible.
 */
#define AST_ARCHIVE_GIVE_ARCHIVE_ACCESS(t_type) \
  protected:                                    \
  t_type() = default;                           \
                                                \
  friend cereal::access

//! Cut down on code duplication for a commonly reused method.
#define AST_ARCHIVE_DEFINE_SERIALIZE_METHOD() \
  template<typename Archive>                  \
  auto serialize([[maybe_unused]] Archive& t_archive) -> void

//! In the case the serializiation method is needed, but does nothing.
#define AST_ARCHIVE_DEFINE_SERIALIZE_METHOD_NIL() \
  AST_ARCHIVE_DEFINE_SERIALIZE_METHOD()           \
  {}

//! Macro for making a type serializable by the cereal library.
#define AST_ARCHIVE_MAKE_ARCHIVEABLE(t_type) \
  AST_ARCHIVE_GIVE_ARCHIVE_ACCESS(t_type);   \
                                             \
  public:                                    \
  AST_ARCHIVE_DEFINE_SERIALIZE_METHOD()

//! Macro for easily archiving nodes dependent on traits.
#define AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(t_type, ...)           \
  AST_ARCHIVE_MAKE_ARCHIVEABLE(t_type)                             \
  {                                                                \
    archive_traits<Archive, t_type, __VA_ARGS__>(t_archive, this); \
  }

//! This is needed for listing the relationship of the base class.
#define REGISTER_ARCHIVEABLE_TYPE(t_namespace, t_type)           \
  CEREAL_REGISTER_TYPE_WITH_NAME(t_namespace::t_type, #t_type)   \
  CEREAL_REGISTER_POLYMORPHIC_RELATION(ast::node::NodeInterface, \
                                       t_namespace::t_type);

#endif // CROW_CROW_AST_ARCHIVE_ARCHIVE_HPP
