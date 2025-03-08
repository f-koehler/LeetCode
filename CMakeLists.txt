cmake_minimum_required(VERSION 3.12)
project(LeetCode CXX)

add_subdirectory(external/Catch2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

include(sources.cmake)
add_executable(LeetCode main.cpp util/tree.cpp ${LEET_CODE_SOURCES})
target_link_libraries(LeetCode PRIVATE Catch2::Catch2WithMain)
target_include_directories(LeetCode PRIVATE util)

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
