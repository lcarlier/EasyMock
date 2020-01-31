/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AutoCleanVectorPtr.h
 * Author: lcarlier
 *
 * Created on July 24, 2019, 11:35 PM
 */

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

  iterator begin() { return m_vect.begin(); }
  const_iterator begin() const { return m_vect.begin(); }
  iterator end() { return m_vect.end(); }
  const_iterator end() const { return m_vect.end(); }
  void push_back(T* elem) { m_vect.push_back(elem); }
  typename std::vector<T*>::size_type size() const { return m_vect.size(); }
  T& operator[](int i) const { return *m_vect[i]; }
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
                { return *lhs == * rhs; });
  }
  bool operator!=(const AutoCleanVectorPtr &other) const
  {
    return (*this == other) == false;
  }
  AutoCleanVectorPtr() {}
  AutoCleanVectorPtr(std::initializer_list<T*> l) :
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

