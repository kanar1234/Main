class ProductofArrayExceptSelf {
    public static void main(String[] args){

    }

    public int[] productExceptSelf(int[] nums) {
        int total = 1;
        int zero = 0;
        for(int i : nums){
            if(i != 0)
                total *= i;
            else
                zero ++;
        }

        for(int i = 0; i < nums.length; i++){
            if(zero > 1){
                nums[i] = 0;
            } else if(zero > 0){
                if(nums[i] != 0)
                    nums[i] = 0;
                else
                    nums[i] = total;
            } else {
                nums[i] = total/nums[i];
            }
        }
        return nums;
    }
}