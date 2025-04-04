import java.util.Arrays;
class findMinInArray {
    public int findMin(int[] nums) {
        // System.out.println(Arrays.toString(nums));
        if(nums.length == 2)
            return Math.min(nums[0], nums[1]);
        if(nums.length == 1)
            return nums[0];
        return Math.min(findMin(Arrays.copyOfRange(nums, 0, nums.length/2)), findMin(Arrays.copyOfRange(nums, nums.length/2, nums.length)));
    }
}