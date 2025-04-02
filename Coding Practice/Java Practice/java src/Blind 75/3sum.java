import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

class ThreeSum {
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> out = new ArrayList<>();
        if (nums.length < 3) {
            return out; // If less than 3 numbers, no triplets possible
        }

        Arrays.sort(nums); // Sort the array

        for (int i = 0; i < nums.length - 2; i++) {
            // Skip duplicate values for the first number
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int target = -nums[i]; // We want nums[l] + nums[r] = -nums[i]
            int l = i + 1;
            int r = nums.length - 1;

            while (l < r) {
                int sum = nums[l] + nums[r];

                if (sum == target) {
                    out.add(Arrays.asList(nums[i], nums[l], nums[r]));

                    // Move pointers and skip duplicates
                    while (l < r && nums[l] == nums[l + 1]) l++;
                    while (l < r && nums[r] == nums[r - 1]) r--;

                    l++;
                    r--;
                } else if (sum < target) {
                    l++; // Increase the left pointer to get a larger sum
                } else {
                    r--; // Decrease the right pointer to get a smaller sum
                }
            }
        }

        return out;
    }
}