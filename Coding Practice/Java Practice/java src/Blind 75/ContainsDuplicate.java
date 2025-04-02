import java.util.HashMap;
import java.util.Map;
public class ContainsDuplicate {
    public static void main(String[] args){

    }
    public boolean containsDuplicate(int[] nums) {
        Map<Integer, Integer> map = new HashMap<>();
        for(int i : nums){
            if(map.get(i) != null)
                return true;
            map.put(i, 0);
        }
        return false;
    }
}