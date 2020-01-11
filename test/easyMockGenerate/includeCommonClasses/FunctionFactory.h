#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H

#include <Function.h>
#include <string>
#include <cstdint>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>
#include <cstring>
#include <iostream>
#include <easyMock.h>

namespace EasyMockTestCase {
  typedef enum
  {
    OneExpect,
    NoExpect,
    NotEnoughCall,
    ThreeExpects,
    OneExpectArgIsBad,
    SecondExpectArgIsBad,
  } TestCase;

  const unsigned int ThreeExpects_NbExpects = 3;
}

/*
 * Helper fomr: https://stackoverflow.com/questions/48504762/combine-tuples-in-a-loop
 */
template <typename F, std::size_t ... Is>
auto tuple_generator_seq(F&& f, std::index_sequence<Is...>)
{
    const decltype(f(0u)) arr[] = {f(Is)...}; // To force order of evaluation
    return std::make_tuple(arr[Is]...);
}

template <std::size_t N, typename F>
auto tuple_generator(F&& f)
{
    return tuple_generator_seq(f, std::make_index_sequence<N>());
}

/*
 * Helper from: https://stackoverflow.com/questions/4770968/storing-function-pointer-in-stdfunction
 */
template <typename Signature>
std::function<Signature> cast(void* f)
{
    return reinterpret_cast<Signature*>(f);
}

/*
 * Helper from: https://stackoverflow.com/questions/37029886/how-to-construct-a-tuple-from-an-array
 */
template <class... Formats, class T, size_t N, size_t... Is>
std::tuple<Formats...> as_tuple_int(std::array<T, N> const& arr,
                                std::index_sequence<Is...>) {
    return std::make_tuple(Formats{arr[Is]}...);
}

template <class... Formats, class T, size_t N,
          class = std::enable_if_t<(N == sizeof...(Formats))>>
std::tuple<Formats...> as_tuple(std::array<T, N> const& arr) {
    return as_tuple_int<Formats...>(arr, std::make_index_sequence<N>{});
}

// Declaration of a templated class. The template can take n parameters
template<typename ...>
class FunctionFactory;

// Specialisation of the template. Out of the n parameters, the first is RV, second is std::tuple<Params...>, and third is std::tuple<Compare ...>
template<typename RV, typename ... Params, typename ... Compare>
class FunctionFactory<RV, std::tuple<Params ...>, std::tuple<Compare ...>>
{
public:
  virtual Function functionFactory() = 0;
  virtual Function* newFunctionFactory() = 0;
  virtual std::string functionGetFunctionName() = 0;
  virtual void setupTestCase(EasyMockTestCase::TestCase tc) = 0;
  virtual std::string getFilename() = 0;
  std::string functionGetMockDir()
  {
    std::string mockDir("mock");
    mockDir.append(functionGetFunctionName());

    return mockDir;
  }
  std::string functionGetIncludeDir()
  {
    std::string includeDir("include/");
    includeDir.append(functionGetFunctionName());
    includeDir.append(".h");

    return includeDir;
  }

  void call_fptr_expect(void* fptr_expect)
  {
    std::tuple<Compare...> t;
    if(!m_compare.empty())
    {
      t = m_compare.front();
      m_compare.pop_front();
    }
    else
    {
      const std::size_t nbCompare = sizeof...(Compare);
      t = tuple_generator<nbCompare>([&](int){ return nullptr; });
    }
    p_call_fptr_expect(fptr_expect, t);
  }

#if 0 //Not yet used
  void call_fptr_expect(void* fptr_expect, Compare ... fptr_compare)
  {
    p_call_fptr_expect(fptr_expect, std::make_tuple(fptr_compare...));
  }
#endif

  RV call_fptr(void *fPtr)
  {
    std::function<RV(Params...)> f = cast<RV(Params...)>(fPtr);
    std::tuple<Params...> p;
    if(!m_params.empty())
    {
      p = m_params.front();
      m_params.pop_front();
    }
    return std::apply(f, p);
  }

  RV get_expected_rv()
  {
    RV expected_rv;
    std::memset(&expected_rv, 0, sizeof(expected_rv));
    if(!m_expect_rv_cur_call.empty())
    {
      expected_rv = m_expect_rv_cur_call.front();
      m_expect_rv_cur_call.pop_front();
    }
    return expected_rv;
  }

  bool is_rv_queue_empty()
  {
    return m_rv.empty();
  }

  bool is_expect_rv_cur_call_queue_empty()
  {
    return m_expect_rv_cur_call.empty();
  }

  bool is_params_queue_empty()
  {
    return m_params.empty();
  }

  bool is_expects_queue_empty()
  {
    return m_expects.empty();
  }

  bool is_compare_queue_empty()
  {
    return m_compare.empty();
  }

  const std::deque<std::tuple<Params...>>& get_params_queue()
  {
    return m_params;
  }

  const std::deque<std::tuple<Params...>>& get_expects_queue()
  {
    return m_expects;
  }

  virtual ~FunctionFactory() {}

protected:
  std::deque<RV> m_rv;
  std::deque<RV> m_expect_rv_cur_call;
  std::deque<std::tuple<Params...>> m_params;
  std::deque<std::tuple<Params...>> m_expects;
  std::deque<std::tuple<Compare...>> m_compare;

private:
  void p_call_fptr_expect(void* fptr_expect, std::tuple<Compare ...> &comparator_fptr_tuple)
  {
    std::function<RV(Params..., RV, Compare ...)> f = cast<RV(Params..., RV, Compare ...)>(fptr_expect);
    std::tuple<Params...> p;
    if(!m_expects.empty())
    {
      p = m_expects.front();
    }
    if(!m_rv.empty())
    {
      m_expect_rv_cur_call.push_back(m_rv.front());
    }
    RV rv;
    std::memset(&rv, 0, sizeof(rv));
    if(!m_rv.empty())
    {
      rv = m_rv.front();
    }
    auto allParam = std::tuple_cat(p, std::make_tuple(rv), comparator_fptr_tuple);
    if(!m_rv.empty())
    {
      m_rv.pop_front();
    }
    if(!m_expects.empty())
    {
      m_expects.pop_front();
    }
    std::apply(f, allParam);
  }
};

#endif /* FUNCTIONFACTORY_H */

