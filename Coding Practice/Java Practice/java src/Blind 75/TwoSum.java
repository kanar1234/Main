import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class TwoSum {
    public static void main(String[] args) {
        int[] nums = new int[]{1,3,4,5,7};
        int target = 9;
        System.out.println(Arrays.toString(twoSum(nums, target)));
    }

    //Start from the lowest value in either array and go up until you reach halfway
    public static int[] twoSum(int[] nums, int target) {

        Map<Integer, Integer> map = new HashMap<>();

        for(int i = 0; i < nums.length; i++){
            int complement = target - nums[i];
            if(map.containsKey(complement)) {
                return new int[]{map.get(complement), i};
            }
            map.put(nums[i], i);
        }

        return new int[]{};
    }
}