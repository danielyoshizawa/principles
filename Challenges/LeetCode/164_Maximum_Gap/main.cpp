// 164 Maximum Gap

// Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.

// You must write an algorithm that runs in linear time and uses linear extra space.

 

// Example 1:

// Input: nums = [3,6,9,1]
// Output: 3
// Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.

// Example 2:

// Input: nums = [10]
// Output: 0
// Explanation: The array contains less than 2 elements, therefore return 0.

 

// Constraints:

//     1 <= nums.length <= 105
//     0 <= nums[i] <= 109

#include <cassert>
#include <vector>
#include <climits>
#include <algorithm>

class Solution {
public:
    int maximumGap(std::vector<int>&& nums) {
        if (nums.size() < 2) return 0;

        std::sort(nums.begin(), nums.end());
        int max_gap = INT_MIN;
        for(int i = 1; i < nums.size(); ++i)
        {
            max_gap = std::max(max_gap, (nums[i] - nums[i-1]));
        }
        return max_gap;
    }
};

int main()
{
    Solution sol;
    assert(sol.maximumGap({3,6,9,1}) == 3);
    assert(sol.maximumGap({10}) == 0);
    assert(sol.maximumGap({100,3,2,1}) == 97);

    return 0;
}