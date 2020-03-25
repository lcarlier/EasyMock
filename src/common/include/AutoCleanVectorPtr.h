#ifndef AUTOCLEANVECTORPTR_H
#define AUTOCLEANVECTORPTR_H

#include <vector>

/*
 * AutoCleanVectorPtr can be used only to store pointers allocated with the 'new' operator
 */
template <class T>
class AutoCleanVectorPtr
{
public:
  typedef typename std::vector<T*>::iterator iterator;
  typedef typename std::vector<T*>::const_iterator const_iterator;
  typedef typename std::vector<T*>::size_type size_type;

  iterator begin() { return m_vect.begin(); }
  const_iterator begin() const { return m_vect.begin(); }
  iterator end() { return m_vect.end(); }
  const_iterator end() const { return m_vect.end(); }
  void push_back(T* elem) { m_vect.push_back(elem); }
  typename std::vector<T*>::size_type size() const { return m_vect.size(); }
  T& operator[](int i) { return *m_vect[i]; }
  const T& operator[](int i) const { return *m_vect[i]; }
  T& front() const { return *m_vect.front(); }
  T& back() const { return *m_vect.back(); }

  AutoCleanVectorPtr(const AutoCleanVectorPtr &other)
  {
    copyObject(other);
  }
  AutoCleanVectorPtr& operator=(AutoCleanVectorPtr other)
  {
    swap(*this, other);

    return *this;
  }
  AutoCleanVectorPtr(AutoCleanVectorPtr &&other)
  {
    swap(*this, other);
  }
  //With elision pattern, no need for a move consutructor

  bool operator==(const AutoCleanVectorPtr &other) const
  {
    return m_vect.size() == other.m_vect.size() &&
            std::equal(m_vect.begin()      ,       m_vect.end(),
                       other.m_vect.begin(), other.m_vect.end(),
                [](const T* lhs, const T* rhs)
                {
                  return *lhs == *rhs;
                });
  }
  bool operator!=(const AutoCleanVectorPtr &other) const
  {
    return (*this == other) == false;
  }
  AutoCleanVectorPtr() {}

  /*
   * When using this class, users have to use an explicit
   * constructor and not the brace-init-list alone. This is an attempt to prevent
   * wrong function calls when a function has an overload with a primitive type
   * at the same place as the AutoCleanVectorPtr class.
   * Thanks to that, people reading this code will (hopefully) take the "good practice"
   * of using the explicit constructor because they will see it everywhere
   * in this code base
   *
   * e.g.
   * Considering the following functions
   * (1) void fun(std::string bar, bool aBool);
   * (2) void fun(std::string bar, AutoCleanVectorPtr<int*> list);
   *
   * When calling
   * fun("bar", {new int(1)});
   * the compiler selects (1) iso (2)
   *
   * WARNING!!!!!!
   * fun("bar", {new int(1), new int(2)});
   * selects (2)!!!!!!!!!!!!!!!!!!!!!
   *
   * The "wrong" function is picked by the compiler
   * when the list initialiser contains only 1 element
   *
   * Because of the keyword explicity, the following is not valid anymore
   * AutoCleanVectorPtr<int*> t = {new int(5)};
   * but I don't think it is a problem since the following works
   * AutoCleanVectorPtr<int*> t({new int(5)});
   *
   * See the following links for more info:
   * https://stackoverflow.com/questions/31896298/why-does-c-allow-stdinitializer-list-to-be-coerced-to-primitive-types-and-b
   */
  explicit AutoCleanVectorPtr(std::initializer_list<T*> l) :
  m_vect(l) {}
  ~AutoCleanVectorPtr()
  {
    clearVector();
  }

private:
  std::vector<T*> m_vect;

  friend void swap(AutoCleanVectorPtr &first, AutoCleanVectorPtr &second)
  {
    std::swap(first.m_vect, second.m_vect);
  }

  void copyObject(const AutoCleanVectorPtr &c)
  {
    typename std::vector<T*>::size_type curElem;
    for(curElem = 0; curElem <  c.m_vect.size() ; curElem++)
    {
      m_vect.push_back(c.m_vect[curElem]->clone());
    }
  }
  void clearVector()
  {
    while(m_vect.size() != 0)
    {
      T* elem = m_vect.back();
      m_vect.pop_back();
      delete elem;
    }
  }
};

#endif /* AUTOCLEANVECTORPTR_H */

