set(EASYMOCK_FRAMEWORK EasyMockFramework)
set(EASYMOCK_FRAMEWORK_INCLUDE_DIR ${EasyMock_SOURCE_DIR}/src/easyMockFramework/include)

set(EASYMOCK_FRAMEWORK_SOURCE_FILE
  ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock.cpp
  ${EasyMock_SOURCE_DIR}/src/easyMockFramework/src/easyMock_matcher.cpp
)

add_library(${EASYMOCK_FRAMEWORK} SHARED
  ${EASYMOCK_FRAMEWORK_SOURCE_FILE}
)

target_link_libraries(${EASYMOCK_FRAMEWORK} ${LIBUNWIND_LIBRARIES} ${LIBDW_LIBRARIES})

target_include_directories(${EASYMOCK_FRAMEWORK} PRIVATE ${EASYMOCK_FRAMEWORK_INCLUDE_DIR})
