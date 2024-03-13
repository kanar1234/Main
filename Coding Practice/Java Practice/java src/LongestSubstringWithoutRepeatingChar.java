import java.util.HashMap;

public static void main (String[] args){
    int longest = lengthOfLongestSubstring("abcabcbb");
    System.out.println(longest);
}
public static int lengthOfLongestSubstring(String s){
    int longest = 0;
    int start = 0;
    HashMap<Character, Integer> map = new HashMap<>();


    for (int i = 0; i < s.length(); i++) {
        char c = s.charAt(i);
        map.put(c, map.getOrDefault(c, 0) + 1);
        while (map.getOrDefault(c, 0) > 1) {
            map.put(s.charAt(start), map.get(s.charAt(start)) - 1);
            start++;
        }
        longest = Math.max(longest, i - start + 1);
    }
    return longest;
}