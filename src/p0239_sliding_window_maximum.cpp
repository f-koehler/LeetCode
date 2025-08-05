#include <catch2/catch_test_macros.hpp>
#include <deque>
#include <vector>

namespace P0239 {
    class Solution {
      public:
        std::vector<int> maxSlidingWindow(const std::vector<int> &nums, int k) {
            const int length = static_cast<int>(nums.size());
            std::vector<int> result;
            result.reserve(length - k + 1);

            // add new elements to the end of the queue
            //
            // delete last one once the queue has reached a length of k
            std::deque<int> max_queue;

            for (int i = 0; i < length; ++i) {
                const int num = nums[i];

                // remove all previous elements that are smaller than num
                //
                // they will leave the window before the new element, the new
                // one will be the maximum
                //
                // we have to do this from the back, the front element is the
                // largest
                while (!max_queue.empty() && (max_queue.back() < num)) {
                    max_queue.pop_back();
                }

                max_queue.push_back(num);

                // check we have filled a window of k elements
                if (i >= k - 1) {
                    if (i >= k) {
                        // retrieve the element that leaves the window
                        const int num_to_remove = nums[i - k];

                        // the number might have been previously removed due to
                        // the while loop
                        //
                        // if it is still there we remove it
                        //
                        // this is also correct when it is the same as the new
                        // element as it will be conatained twice in the list
                        //
                        // there will be at least one element in the queue (the
                        // new one)
                        if (num_to_remove == max_queue.front()) {
                            max_queue.pop_front();
                        }
                    }

                    // the largest element will be at the front of the queue
                    result.push_back(max_queue.front());
                }
            }

            return result;
        }
    };

    TEST_CASE("0239 - Sliding Window Maximum",
              "[Array][Queue][Sliding Window][Heap (Priority Queue)][Monotonic "
              "Queue]") {

        SECTION("Example 1") {
            // Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
            // Output: [3,3,5,5,6,7]
            Solution s;
            REQUIRE(s.maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3) ==
                    std::vector<int>{3, 3, 5, 5, 6, 7});
        }

        SECTION("Example 2") {
            // Input: nums = [1], k = 1
            // Output: [1]
            Solution s;
            REQUIRE(s.maxSlidingWindow({1}, 1) == std::vector<int>{1});
        }

        SECTION("Example 3") {
            // Input: nums = [7,2,4], k = 2
            // Output: [7,4]
            Solution s;
            REQUIRE(s.maxSlidingWindow({7, 2, 4}, 2) == std::vector<int>{7, 4});
        }
    }
} // namespace P0239
