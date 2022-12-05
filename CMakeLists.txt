cmake_minimum_required(VERSION 3.12)
project(LeetCode CXX)

add_subdirectory(Catch2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

add_executable(LeetCode main.cpp
    000/001_two_sum.cpp
    000/021_merge_two_sorted_lists.cpp
    000/088_merge_sorted_array.cpp
    200/206_reverse_linked_list.cpp
    800/876_middle_of_the_linked_list.cpp
)
target_link_libraries(LeetCode PRIVATE Catch2::Catch2WithMain)

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