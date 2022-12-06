cmake_minimum_required(VERSION 3.12)
project(LeetCode CXX)

add_subdirectory(Catch2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(LeetCode main.cpp
    0000/0001_two_sum.cpp
    0000/0002_add_two_numbers.cpp
    0000/0009_palindrome_number.cpp
    0000/0021_merge_two_sorted_lists.cpp
    0000/0088_merge_sorted_array.cpp
    0100/0118_pascals_triangle.cpp
    0200/0206_reverse_linked_list.cpp
    0500/0566_reshape_the_matrix.cpp
    0800/0876_middle_of_the_linked_list.cpp
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