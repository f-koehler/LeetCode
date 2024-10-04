cmake_minimum_required(VERSION 3.12)
project(LeetCode CXX)

add_subdirectory(Catch2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(
  LeetCode
  main.cpp
  0000/0001_two_sum.cpp
  0000/0002_add_two_numbers.cpp
  0000/0009_palindrome_number.cpp
  0000/0019_remove_nth_node_from_end_of_list.cpp
  0000/0021_merge_two_sorted_lists.cpp
  0000/0027_remove_element.cpp
  0000/0042_trapping_rain_water.cpp
  0000/0050_pow_x_n.cpp
  0000/0088_merge_sorted_array.cpp
  0100/0118_pascals_triangle.cpp
  0200/0206_reverse_linked_list.cpp
  0200/0238_product_of_array_except_self.cpp
  0200/0258_add_digits.cpp
  0500/0557_reverse_words_in_a_string_iii.cpp
  0500/0566_reshape_the_matrix.cpp
  0700/0733_flood_fill.cpp
  0800/0876_middle_of_the_linked_list.cpp
  1900/1929_concatenation_of_array.cpp
  2400/2469_convert_the_temperature.cpp)
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
