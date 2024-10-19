cmake_minimum_required(VERSION 3.12)
project(LeetCode CXX)

find_package(Catch2 REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(
  LeetCode
  main.cpp
  util/tree.cpp
  0000/0001_two_sum.cpp
  0000/0002_add_two_numbers.cpp
  0000/0009_palindrome_number.cpp
  0000/0019_remove_nth_node_from_end_of_list.cpp
  0000/0021_merge_two_sorted_lists.cpp
  0000/0027_remove_element.cpp
  0000/0042_trapping_rain_water.cpp
  0000/0050_pow_x_n.cpp
  0000/0069_sqrt_x.cpp
  0000/0088_merge_sorted_array.cpp
  0100/0104_maximum_depth_of_binary_tree.cpp
  0100/0112_path_sum.cpp
  0100/0118_pascals_triangle.cpp
  0100/0136_single_number.cpp
  0100/0151_reverse_words_in_a_string.cpp
  0200/0206_reverse_linked_list.cpp
  0200/0238_product_of_array_except_self.cpp
  0200/0258_add_digits.cpp
  0200/0283_move_zeroes.cpp
  0300/0338_counting_bits.cpp
  0300/0345_reverse_vowels_of_a_string.cpp
  0300/0392_is_subsequence.cpp
  0400/0443_string_compression.cpp
  0400/0450_delete_node_in_a_bst.cpp
  0500/0506_relative_ranks.cpp
  0500/0557_reverse_words_in_a_string_iii.cpp
  0500/0566_reshape_the_matrix.cpp
  0600/605_can_place_flowers.cpp
  0600/643_maximum_average_subarray_i.cpp
  0700/0724_find_pivot_index.cpp
  0700/0733_flood_fill.cpp
  0700/0735_asteroid_collision.cpp
  0800/0841_keys_and_rooms.cpp
  0800/0872_leaf_similar_trees.cpp
  0800/0876_middle_of_the_linked_list.cpp
  0900/0933_number_of_recent_calls.cpp
  1000/1071_greatest_common_divisor_of_strings.cpp
  1100/1137_nth_tribonacci_number.cpp
  1300/1318_minimum_flips_to_make_a_or_b_equal_to_c.cpp
  1400/1431_kids_with_the_greatest_number_of_candies.cpp
  0700/0700_search_in_a_binary_search_tree.cpp
  1700/1732_find_the_highest_altitude.cpp
  1700/1768_merge_string_alternately.cpp
  1900/1929_concatenation_of_array.cpp
  2200/2215_find_the_difference_of_two_arrays.cpp
  2400/2469_convert_the_temperature.cpp)
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
