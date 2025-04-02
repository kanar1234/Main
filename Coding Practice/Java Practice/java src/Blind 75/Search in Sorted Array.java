class SearchInSortedArray {
    public int search(int[] nums, int target) {
        int left = 0;
        int right = nums.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent overflow

            // Check if mid is the target
            if (nums[mid] == target) {
                return mid;
            }

            // Determine which part is sorted
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1; // Target is in the left sorted part
                } else {
                    left = mid + 1; // Target is in the right part
                }
            } else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1; // Target is in the right sorted part
                } else {
                    right = mid - 1; // Target is in the left part
                }
            }
        }
        return -1; // Target not found
    }
}