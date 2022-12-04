/*! \file
 *
 * \brief Contains the logic to create a [function factory](md_docs_architecture.html#user-content-fatc).
 */
#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H

#include <FunctionDeclaration.h>
#include <ElementToMockContext.h>
#include <string>
#include <cstdint>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>
#include <cstring>
#include <iostream>
#include <easyMock.h>
#include <type_traits>
#include <unordered_map>
#include <memory>

#undef NDEBUG
#include <cassert>

/*!
 * \brief Namespace containing data type useful for testing.
 */
namespace EasyMockTestCase
{
  /*!
   * \brief Represents each test case that the generic generate tests has.
   *
   * The value of the enum is given to the factory so that the factory
   * can configure the correct amount of expect and return.
   */
  enum class TestCase
  {
    /*!
     * \brief Test case expecting 1 call to the mocked function without error.
     */
    OneExpect,
    /*!
     * \brief Test case expecting an error when a mocked function is called
     * without being expected.
     */
    NoExpect,
    /*!
     * \brief Test case expecting an error when the number of call to the
     * mocked function is not as much as expected.
     */
    NotEnoughCall,
    /*!
     * \brief Test case expecting 3 call to the mocked function without error.
     */
    ThreeExpects,
    /*!
     * \brief Test case expecting an error when the parameter given to the
     * first call of the mock is not as expected.
     */
    OneExpectArgIsBad,
    /*!
     * \brief Test case expecting an error when the parameter given to the
     * second call of the mock is not as expected.
     */
    SecondExpectArgIsBad,
  };

  /*!
   * \brief Represents test cases focusing on testing mocked classes
   *
   * The value of the enum is given to the factory so that the factory
   * can configure the correct amount of expect and return.
   */
  enum class TestCaseClass
  {
    /*!
     * \brief Test case expecting 1 call to the mocked class function without error.
     */
    OneExpectRightClassInstance,
    /*!
     * \brief Test case testing that the wrong class instance is given to the mock.
     */
    OneExpectWrongClassInstance
  };

  const unsigned int ThreeExpects_NbExpects = 3;
  const unsigned int NotEnoughCall_NbExpects = 3;
}

/*
 * GCC doesn't like the anonymous namespace here but we set it for clang
 * to catch any misuse over there
 */
#if defined(__clang__)
namespace
{
#endif
  template<typename RV>
  struct RvContext
  {
    std::deque<RV> m_rv;
    std::deque<RV> m_expect_rv_cur_call;
  };

  template<>
  struct RvContext<void>
  {
  };
#if defined(__clang__)
};
#endif

/*
 * Helper from: https://stackoverflow.com/questions/48504762/combine-tuples-in-a-loop
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

using ElementToMockList = std::vector<std::shared_ptr<FunctionDeclaration>>;

// Specialisation of the template. Out of the n parameters, the first is RV, second is std::tuple<Params...>, and third is std::tuple<Compare ...>
/*!
 * \brief Base interface for all the test factories.
 *
 * See the [architecture page](md_docs_architecture.html#user-content-fatc) for more information about the factories.
 */
template<typename RV, typename ... Params, typename ... Compare>
class FunctionFactory<RV, std::tuple<Params ...>, std::tuple<Compare ...>>
{
public:
  /*!
   * \brief Returns the function to be mocked.
   */
  virtual std::shared_ptr<FunctionDeclaration> functionFactory() {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);}
  /*!
   * \brief Returns all the functions to be mocked within a header file.
   *
   * The first element of this list is the same as the one returned by
   * functionFactory().
   *
   * The parser tests uses the objects returned by this function to check that
   * the parsing is working as expected.
   */
  virtual ElementToMockList functionFactoryArray() {ElementToMockList rv; rv.push_back(functionFactory()); return rv;}
  /*!
   * \brief Returns the list of macro to be generated
   */
  virtual ElementToMockContext::MacroDefinitionList getDefinedMacroList() {ElementToMockContext::MacroDefinitionList  ml; return ml;}
  /*!
   * \brief Returns the name of the function to be tested.
   */
  virtual std::string functionGetFunctionName() = 0;
  /*!
   * \brief Setup the test case based.
   *
   * \param tc Specifies which test case from EasyMockTestCase::TestCase to setup.
   */
  virtual void setupTestCase(EasyMockTestCase::TestCase tc) {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);}
  /*!
   * \brief Returns the name of the matcher function name generated by the mock
   * when a parameter is a struct.
   *
   * This function is only used on test cases testing function with structs
   * and is not implemented by all the factories.
   */
  virtual std::string getMatcherFunctionName() {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);}
  /*!
   * \brief Returns the name of the function parameter which has a field with
   * a wrong value on the EasyMockTestCase::OneExpectArgIsBad test case.
   *
   * This function is only used on test cases testing function with structs
   * and is not implemented by all the factories.
   */
  virtual std::string getFieldWrongName() {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);}
  /*!
   * \brief Returns the name of the field which has a wrong value on the
   * EasyMockTestCase::OneExpectArgIsBad test case.
   *
   * This function is only used on test cases testing function with structs
   * and is not implemented by all the factories.
   */
  virtual std::string getSubFieldWrongName() {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);}
  /*!
   * \brief Returns the type name of the field which has a wrong value on the
   * EasyMockTestCase::OneExpectArgIsBad test case.
   *
   * This function is only used on test cases testing function with structs
   * and is not implemented by all the factories.
   */
  virtual std::string getSubFieldWrongTypeName() {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);}
  /*!
   * \brief Returns the name of the field which has a wrong value on the
   * EasyMockTestCase::OneExpectArgIsBad test case.
   *
   * This function is only used on test cases testing function with structs
   * and is not implemented by all the factories.
   */
  virtual std::string getSubComposableTypeType() {fprintf(stderr, "Function %s must be overriden\n\r", __FUNCTION__); assert(false);}
  /*!
   * \brief Returns the filename containing the function to be tested.
   */
  virtual std::string getFilename() = 0;

  // This constexpr function is actually "overriden" by CppFunctionClassFactory
  constexpr bool isClassMember() { return false; }

  /*!
   * \brief Returns if the factory is for C++
   */
  virtual bool isCpp() { return false; }

  void setupTestCaseAndMatcher(EasyMockTestCase::TestCase tc, EasyMock_Matcher matcher){
    m_user_matcher = matcher;
    this->setupTestCase(tc);
  }

  bool getGenerateTypes()
  {
    return m_generate_types;
  }

  bool loadFunction()
  {
    return m_load_function;
  }

  bool getRmDir()
  {
    return m_rm_dir;
  }

  std::string functionGetMockDir()
  {
    std::string mockDir("mock");
    mockDir.append(functionGetFunctionName());

    return mockDir;
  }
  std::string functionGetIncludeDir()
  {
    std::string includeDir("include/");
    includeDir.append(getFilename());

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

  template<typename F_RV=RV,
           std::enable_if_t<!std::is_void<F_RV>::value, bool> = true
  >
  F_RV call_fptr(void *fPtr)
  {
    std::function<F_RV(Params...)> f = cast<F_RV(Params...)>(fPtr);
    std::tuple<Params...> p;
    if(!m_params.empty())
    {
      p = m_params.front();
      m_params.pop_front();
    }
    return std::apply(f, p);
  }

  template<typename F_RV=RV,
           std::enable_if_t<std::is_void<F_RV>::value, bool> = true
  >
  int call_fptr(void *fPtr)
  {
    std::function<F_RV(Params...)> f = cast<F_RV(Params...)>(fPtr);
    std::tuple<Params...> p;
    if(!m_params.empty())
    {
      p = m_params.front();
      m_params.pop_front();
    }
    std::apply(f, p);
    return 0;
  }

  template<typename F_RV=RV,
           std::enable_if_t<!std::is_void<F_RV>::value, bool> = true
  >
  F_RV get_expected_rv()
  {
    if(!m_rvContext.m_expect_rv_cur_call.empty())
    {
      F_RV expected_rv = m_rvContext.m_expect_rv_cur_call.front();
      m_rvContext.m_expect_rv_cur_call.pop_front();
      return expected_rv;
    }
    return F_RV{};
  }

  template<typename F_RV=RV,
           std::enable_if_t<std::is_void<F_RV>::value, bool> = true
  >
  int get_expected_rv()
  {
    return 0;
  }

  template<typename F_RV=RV,
           std::enable_if_t<!std::is_void<F_RV>::value, bool> = true
  >
  void clear_rv_queues()
  {
    m_rvContext.m_rv.clear();
    m_rvContext.m_expect_rv_cur_call.clear();
  }

  template<typename F_RV=RV,
           std::enable_if_t<std::is_void<F_RV>::value, bool> = true
  >
  void clear_rv_queues()
  {
  }

  void clear_all_queues()
  {
    clear_rv_queues();
    m_params.clear();
    m_expects.clear();
    m_compare.clear();
  }

  template<typename F_RV=RV,
           std::enable_if_t<!std::is_void<F_RV>::value, bool> = true
  >
  bool is_rv_queue_empty()
  {
    return m_rvContext.m_rv.empty();
  }

  template<typename F_RV=RV,
           std::enable_if_t<std::is_void<F_RV>::value, bool> = true
  >
  bool is_rv_queue_empty()
  {
    return true;
  }

  template<typename F_RV=RV,
           std::enable_if_t<!std::is_void<F_RV>::value, bool> = true
  >
  bool is_expect_rv_cur_call_queue_empty()
  {
    return m_rvContext.m_expect_rv_cur_call.empty();
  }

  template<typename F_RV=RV,
           std::enable_if_t<std::is_void<F_RV>::value, bool> = true
  >
  bool is_expect_rv_cur_call_queue_empty()
  {
    return true;
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

  constexpr size_t getNbParams()
  {
    return sizeof...(Params);
  }

protected:
  FunctionFactory() :
      m_generate_types(false),
      m_load_function(true),
      m_rm_dir(true)
    {}
  EasyMock_Matcher m_user_matcher;

  RvContext<RV> m_rvContext;
  std::deque<std::tuple<Params...>> m_params;
  std::deque<std::tuple<Params...>> m_expects;
  std::deque<std::tuple<Compare...>> m_compare;
  bool m_generate_types;
  bool m_load_function;
  bool m_rm_dir;

private:
  template<typename F_RV=RV,
           std::enable_if_t<!std::is_void<F_RV>::value, bool> = true
  >
  void p_call_fptr_expect(void* fptr_expect, std::tuple<Compare ...> &comparator_fptr_tuple)
  {
    std::function<F_RV(Params..., F_RV, Compare ...)> fWithReturn = cast<F_RV(Params..., F_RV, Compare ...)>(fptr_expect);
    std::function<F_RV(Params..., Compare ...)> fWithoutReturn = cast<F_RV(Params..., Compare ...)>(fptr_expect);
    std::tuple<Params...> p;
    if(!m_expects.empty())
    {
      p = m_expects.front();
    }
    if(!m_rvContext.m_rv.empty())
    {
      m_rvContext.m_expect_rv_cur_call.push_back(m_rvContext.m_rv.front());
    }
    if(!m_rvContext.m_rv.empty())
    {
      F_RV rv = m_rvContext.m_rv.front();
      auto allParam = std::tuple_cat(p, std::make_tuple(rv), comparator_fptr_tuple);
      std::apply(fWithReturn, allParam);
    }
    else
    {
      auto allParam = std::tuple_cat(p, comparator_fptr_tuple);
      std::apply(fWithoutReturn, allParam);
    }
    if(!m_rvContext.m_rv.empty())
    {
      m_rvContext.m_rv.pop_front();
    }
    if(!m_expects.empty())
    {
      m_expects.pop_front();
    }
  }

  template<typename F_RV=RV,
           std::enable_if_t<std::is_void<F_RV>::value, bool> = true
  >
  void p_call_fptr_expect(void* fptr_expect, std::tuple<Compare ...> &comparator_fptr_tuple)
  {
    std::function<F_RV(Params..., Compare ...)> fWithoutReturn = cast<F_RV(Params..., Compare ...)>(fptr_expect);
    std::tuple<Params...> p;
    if(!m_expects.empty())
    {
      p = m_expects.front();
    }

    auto allParam = std::tuple_cat(p, comparator_fptr_tuple);
    std::apply(fWithoutReturn, allParam);
    if(!m_expects.empty())
    {
      m_expects.pop_front();
    }
  }
};

#endif /* FUNCTIONFACTORY_H */
