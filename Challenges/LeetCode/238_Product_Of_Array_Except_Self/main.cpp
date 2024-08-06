// 238 Product

// Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

// You must write an algorithm that runs in O(n) time and without using the division operation.

// Example 1:

// Input: nums = [1,2,3,4]
// Output: [24,12,8,6]

// Example 2:

// Input: nums = [-1,1,0,-3,3]
// Output: [0,0,9,0,0]

// Constraints:

//     2 <= nums.length <= 105
//     -30 <= nums[i] <= 30
//     The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

// Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)

#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

class Solution
{
public:
    std::vector<int> productExceptSelf(std::vector<int> &&nums)
    {
        // Multiply except zeros
        std::vector<int> ret(nums.size(), 0);
        int multiplication {1};
        int count_zeros {0};
        for (auto a : nums)
        {
            if (a == 0)
            {
                count_zeros++;
                continue;
            }
            multiplication *= a;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if (count_zeros > 1)
            {
                return ret;
            }
            if (count_zeros == 1)
            {
                if (nums[i] != 0)
                {
                    continue;
                } else {
                    ret[i] = multiplication;
                }
            } else {
                ret[i] = multiplication / nums[i];
            }
        }

        return ret;
    }
};

bool check(const std::vector<int> & result, std::vector<int> && compare)
{
    for (int i = 0; i < result.size(); ++i)
    {
        if (result[i] != compare[i]) return false;
    }
    return true;
}

int main()
{
    Solution sol;
    assert(check(sol.productExceptSelf({1,2,3,4}), {24,12,8,6}));
    assert(check(sol.productExceptSelf({-1,1,0,-3,3}), {0,0,9,0,0}));
    assert(check(sol.productExceptSelf({0,0}), {0,0}));

    return 0;
}