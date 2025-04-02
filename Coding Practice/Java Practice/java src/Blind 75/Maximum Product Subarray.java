class MaximumProductSubarray {
    public int maxProduct(int[] nums) {
        int local_max = nums[0];
        int local_min = nums[0];
        int global_max = nums[0];
        for(int i = 1; i < nums.length; i++){
            if(nums[i-1] == 0){
                local_max = nums[i];
                local_min = nums[i];
            } else {
                int prev_max = local_max;
                int prev_min = local_min;
                local_max = Math.max(Math.max(prev_max * nums[i], prev_min * nums[i]), nums[i]);
                local_min = Math.min(Math.min(prev_max * nums[i], prev_min * nums[i]), nums[i]);
            }
            global_max = Math.max(local_max, global_max);

            // System.out.println("local_max: " + local_max + "\nlocal_min: " + local_min + "\nglobal_max: " + global_max);
        }

        return global_max;
    }
}