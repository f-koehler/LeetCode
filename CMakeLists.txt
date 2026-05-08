cmake_minimum_required(VERSION 3.12)
project(LeetCode CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fconcepts")

find_package(Catch2 CONFIG REQUIRED)
file(GLOB LEET_CODE_SOURCES src/p*.cpp)
add_executable(LeetCode main.cpp util/tree.cpp ${LEET_CODE_SOURCES})
target_link_libraries(LeetCode PRIVATE Catch2::Catch2WithMain stdc++exp)
target_include_directories(LeetCode PRIVATE util)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(LeetCode PRIVATE -fcontract-evaluation-semantic=enforce)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(LeetCode PRIVATE -fcontract-evaluation-semantic=ignore)
endif()

include(CTest)
include(Catch)
enable_testing()
catch_discover_tests(LeetCode)

include(CheckIPOSupported)
check_ipo_supported(RESULT LEET_CODE_IPO_SUPPORTED OUTPUT LEET_CODE_IPO_CHECK_OUTPUT)

if(LEET_CODE_IPO_SUPPORTED)
  set_property(TARGET LeetCode PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(WARNING "IPO is not supported: ${LEET_CODE_IPO_CHECK_OUTPUT}")
endif()
