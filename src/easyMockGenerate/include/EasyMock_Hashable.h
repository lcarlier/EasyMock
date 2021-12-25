/*!
 * \file
 *
 * \brief Contains the implementation of containers using pointers to hashable objects.
 *
 * Any class that wants to be able to use any of the set or map defined in thie file (e.g. ::EasyMock::HashablePointerMap) must
 * inherit from ::EasyMock::Hashable.
 */
#ifndef EASYMOCK_HASHABLE_H
#define EASYMOCK_HASHABLE_H

#include <boost/version.hpp>

#include <cstddef>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <variant>

#include <type_traits>

namespace EasyMock {

  /*!
   * \brief Defines the interface that every EasyMock hashable object must implement.
   */
  struct Hashable {
    /*!
     * \brief Generates a unique hash of this object.
     *
     * \return A unique hash for this object.
     */
    [[nodiscard]] virtual std::size_t getHash() const noexcept = 0;

    /*!
     * \brief Cache the hash of this object so that getHash() gets called faster.
     *
     * The code managing this object can call this function to compute the hash and cache it for performance reason.
     * If this function isn't called, the hash of the object is computed each and every time getHash() is called.
     *
     * A good rule of thumb is to call cacheHash() whenever it is known that the object won't be modified anymore.
     *
     * \warning Modifying a contained type retrieved by functions such as ::Declarator::getType() after calling
     * cacheHash() will result in a wrong hash returned by getHash(). The user is responsible for updating the cache
     * by calling cacheHash() again on all the objects referencing the modified object. e.g.
     *
     * \code{.cpp}
     *
     * auto cType = std::make_shared<CType>(CTYPE_INT);
     *
     * Parameter p1{cType, "p1};
     * p1.cacheHash();
     * Parameter p1{cType, "p2};
     * p2.cacheHash();
     * // cType is referenced by p1 and p2
     *
     * cType.setUnsigned(true);
     * // Cache of p1 and p2 needs to be updated otherwise getCache() would return the wrong value.
     *
     * p1.cacheHash();
     * p2.cacheHash();
     * \endcode
     */
    virtual void cacheHash() noexcept = 0;

    virtual ~Hashable() = default;
  };

  /*!
   * \brief Struct used to get the hash of an ::EasyMock::Hashable object pointer.
   */
  template<typename T>
  struct HashableHash {
    inline size_t operator()(const T &pointer) const noexcept
    {
      static_assert(std::is_pointer<T>::value, "The template parameter must be a pointer");
      static_assert(std::is_base_of<Hashable, typename std::remove_pointer<T>::type>::value,
                    "The template parameter must inherit from EasyMock_Hashable");
      return pointer->getHash();
    }
  };

  /*!
   * \brief Struct used to get the hash of an ::EasyMock::Hashable object pointer.
   */
  template<typename T>
  struct EasyMock_HashableHashEqualTo {
    inline bool operator()(const T &lhs, const T &rhs) const noexcept
    {
      static_assert(std::is_pointer<T>::value, "The template parameter must be a pointer");
      static_assert(std::is_base_of<Hashable, typename std::remove_pointer<T>::type>::value,
                    "The template parameter must inherit from EasyMock_Hashable");
      /*
       * Instead of comparing the objects, the hashes are compared. It is very important that the hashes are
       * cached otherwise the performance is horrible.
       */
      return lhs->getHash() == rhs->getHash();
    }
  };

  /*!
   * \brief Templated class to be used to declare a ::EasyMock::HashablePointerMap.
   *
   * A ::EasyMock::HashablePointerMap has the same functionality as a std::map
   *
   * \tparam K The key type of the map. It must inherit from ::EasyMock::Hashable.
   * \tparam T The value type of the map.
   */
  template<typename K, typename T>
  class HashablePointerMap : public std::map<K, T, HashableHash<K>, EasyMock_HashableHashEqualTo<K>>
  {};

  /*!
   * \brief Templated class to be used to declare a ::EasyMock::HashablePointerUnorderedMap.
   *
   * A ::EasyMock::HashablePointerUnorderedMap has the same functionality as a std::unordered_map
   *
   * \tparam K The key type of the unordered map. It must inherit from ::EasyMock::Hashable.
   * \tparam T The value type of the map.
   */
  template<typename K, typename T>
  class HashablePointerUnorderedMap : public std::unordered_map<K, T, HashableHash<K>, EasyMock_HashableHashEqualTo<K>>
  {};

  /*!
   * \brief Templated class to be used to declare a ::EasyMock::HashablePointerUnorderedSet.
   *
   * A ::EasyMock::HashablePointerUnorderedSet has the same functionality as a std::unordered_set
   *
   * \tparam K The key type of the unordered set. It must inherit from ::EasyMock::Hashable.
   */
  template<typename K>
  class HashablePointerUnorderedSet : public std::unordered_set<K, HashableHash<K>, EasyMock_HashableHashEqualTo<K>>
  {};

  /*!
   * \brief hash_value function called by boost for the EasyMock classes
   *
   * Thanks to this templated function and the fact that all the EasyMock classes
   * implement getHash. We can have such call:
   *
   * \code{.cpp}
   * boost::hash_combine(seed, *m_type); //m_elem is a TypeItf*
   * \endcode
   *
   * I.E. The hash_value function is automatically generated by the compiler for every class inheriting from
   * ::EasyMock::Hashable object.
   */
  template<typename T>
  auto hash_value(const T &t) noexcept -> decltype(t.getHash())
  {
    return t.getHash();
  }

  // Manual patch up for boost version under 1.67 for std::variant support.
  // When support for Ubuntu 18.04 is removed, this code can also be removed.
#if BOOST_VERSION < 106700
  template<typename T> struct is_variant : std::false_type {};

  template<typename ...Args>
  struct is_variant<std::variant<Args...>> : std::true_type {};

  template<typename T>
  inline constexpr bool is_variant_v=is_variant<T>::value;

  template
  <
    typename T,
    typename std::enable_if<is_variant<T>{},bool>::type = true
  >
  auto hash_value(const T &t) noexcept
  {
    return std::visit([](auto&& t) -> decltype(t.getHash()) {
      return t.getHash();
    }, t);
  }
#endif

}

#endif /* EASYMOCK_HASHABLE_H */
