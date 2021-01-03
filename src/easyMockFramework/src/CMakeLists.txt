set(EASYMOCK_FRAMEWORK_LIBRARY_INCLUDE_DIR ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include ${EasyMock_SOURCE_DIR}/src/common/include ${Boost_INCLUDE_DIR})

set(EASYMOCK_FRAMEWORK_LIBRARY_SOURCE_FILE
  ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock_matcher.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/cstring.c
  ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/MockedFunction.c
)

add_library(${EASYMOCK_FRAMEWORK_LIBRARY} SHARED
  ${EASYMOCK_FRAMEWORK_LIBRARY_SOURCE_FILE}
)

target_link_libraries(${EASYMOCK_FRAMEWORK_LIBRARY} ${LIBUNWIND_LIBRARIES} ${LIBDW_LIBRARIES})

target_include_directories(${EASYMOCK_FRAMEWORK_LIBRARY} PRIVATE ${EASYMOCK_FRAMEWORK_LIBRARY_INCLUDE_DIR})
