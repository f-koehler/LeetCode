cmake_minimum_required(VERSION 3.12)
project(LeetCode CXX)

add_subdirectory(external/Catch2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(
  LeetCode
  main.cpp
  util/tree.cpp
  src/0001_two_sum.cpp
  src/0002_add_two_numbers.cpp
  src/0009_palindrome_number.cpp
  src/0017_letter_combinations_of_a_phone_number.cpp
  src/0019_remove_nth_node_from_end_of_list.cpp
  src/0021_merge_two_sorted_lists.cpp
  src/0027_remove_element.cpp
  src/0042_trapping_rain_water.cpp
  src/0050_pow_x_n.cpp
  src/0069_sqrt_x.cpp
  src/0088_merge_sorted_array.cpp
  src/0104_maximum_depth_of_binary_tree.cpp
  src/0112_path_sum.cpp
  src/0118_pascals_triangle.cpp
  src/0136_single_number.cpp
  src/0151_reverse_words_in_a_string.cpp
  src/0206_reverse_linked_list.cpp
  src/0238_product_of_array_except_self.cpp
  src/0258_add_digits.cpp
  src/0283_move_zeroes.cpp
  src/0334_increasing_triplet_subsequence.cpp
  src/0338_counting_bits.cpp
  src/0345_reverse_vowels_of_a_string.cpp
  src/0392_is_subsequence.cpp
  src/0443_string_compression.cpp
  src/0450_delete_node_in_a_bst.cpp
  src/0506_relative_ranks.cpp
  src/0557_reverse_words_in_a_string_iii.cpp
  src/0566_reshape_the_matrix.cpp
  src/605_can_place_flowers.cpp
  src/643_maximum_average_subarray_i.cpp
  src/0700_search_in_a_binary_search_tree.cpp
  src/0724_find_pivot_index.cpp
  src/0733_flood_fill.cpp
  src/0735_asteroid_collision.cpp
  src/0746_min_cost_climbing_stairs.cpp
  src/0841_keys_and_rooms.cpp
  src/0872_leaf_similar_trees.cpp
  src/0876_middle_of_the_linked_list.cpp
  src/0933_number_of_recent_calls.cpp
  src/1071_greatest_common_divisor_of_strings.cpp
  src/1137_nth_tribonacci_number.cpp
  src/1318_minimum_flips_to_make_a_or_b_equal_to_c.cpp
  src/1431_kids_with_the_greatest_number_of_candies.cpp
  src/1732_find_the_highest_altitude.cpp
  src/1768_merge_string_alternately.cpp
  src/1926_nearest_exit_from_entrance_in_maze.cpp
  src/1929_concatenation_of_array.cpp
  src/2215_find_the_difference_of_two_arrays.cpp
  src/2469_convert_the_temperature.cpp)
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
