// Day 3 - Two Pointers Technique
// Topics Covered:
// 1. When to use Two Pointers (Pattern)
// 2. Pair Sum Problem (Sorted Array)
// 3. Remove Duplicates from Sorted Array
// 4. Container With Most Water (Intro)

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------------
// 1. PAIR SUM PROBLEM (SORTED ARRAY)
// --------------------------------------------------
bool pairSum(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target)
            return true;
        else if (sum < target)
            left++;
        else
            right--;
    }
    return false;
}

// --------------------------------------------------
// 2. REMOVE DUPLICATES FROM SORTED ARRAY (IN-PLACE)
// --------------------------------------------------
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int i = 0;
    for (int j = 1; j < nums.size(); j++) {
        if (nums[j] != nums[i]) {
            i++;
            nums[i] = nums[j];
        }
    }
    return i + 1;
}

// --------------------------------------------------
// 3. CONTAINER WITH MOST WATER (INTRO)
// --------------------------------------------------
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;

    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        maxWater = max(maxWater, width * h);

        if (height[left] < height[right])
            left++;
        else
            right--;
    }
    return maxWater;
}

// --------------------------------------------------
// MAIN FUNCTION (TESTING ALL TOPICS)
// --------------------------------------------------
int main() {

    // Pair Sum
    vector<int> arr = {1, 2, 4, 7, 11, 15};
    int target = 15;
    cout << "Pair Sum Exists: "
         << (pairSum(arr, target) ? "Yes" : "No") << endl;

    // Remove Duplicates
    vector<int> nums = {1,1,2,2,3,3,3,4};
    int newLength = removeDuplicates(nums);
    cout << "After Removing Duplicates: ";
    for (int i = 0; i < newLength; i++)
        cout << nums[i] << " ";
    cout << endl;

    // Container With Most Water
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    cout << "Max Water Container Area: "
         << maxArea(height) << endl;

    return 0;
}
