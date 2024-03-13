## Description:
## Given a string, find the longest, non-repeated substring

class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        nonDupe = ""
        longest = 0
        stored = []
        if len(s) < 1:
            return 0
        if len(s) == 1:
            return 1
        for i in range(len(s)):
            if s[i] not in nonDupe and i != (len(s)-1):
                nonDupe += s[i]
            else:
                stored.append(nonDupe)
                while s[i] in nonDupe:
                    nonDupe = nonDupe[1::]
                nonDupe += s[i]
                if i == len(s)-1:
                    stored.append(nonDupe)
        return len(max(stored, key = len))
		
## How it works:
## You read the array left to right and store each letter you see 
## in a temporary string. When you read a character that already exists
## in the temporary string, you append the temporary string to a new
## array and set the temporary string to the current character.
## After reaching the end of the array, we store the last temporary
## string to our array then we return the length of the longest string
## in our array

## Runtime: O(n^2) since we need to loop through our string and our temporary string
## Memory Usage: O(n) since we need to store the temporary strings into an array