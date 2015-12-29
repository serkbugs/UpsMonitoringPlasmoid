cmake_policy(SET CMP0063 NEW)
INCLUDE_DIRECTORIES( ${upsdataenginecpp_SOURCE_DIR} )
MESSAGE( "source dir ${CMAKE_SOURCE_DIR}  bin dir ${CMAKE_BINARY_DIR}" )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=c++11")

INCLUDE_DIRECTORIES (
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/test
)

set(ups_tests_SRCS
    UpsTests.cpp
)

SET(TEST_LIBRARIES ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})

ADD_EXECUTABLE( UpsTests ${ups_tests_SRCS} )
TARGET_LINK_LIBRARIES( UpsTests ${TEST_LIBRARIES} nutclient)
ADD_TEST( NAME UpsTests COMMAND UpsTests )

