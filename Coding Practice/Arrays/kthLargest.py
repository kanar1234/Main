## Description:
## Given an int array and an integer, k, find the kth largest
## integer in the the array 

class Solution(object):
    def kthLargest(array, k):
        array.sort(reverse = True)
        pointer = 0
        k -= 1
        while k > 0 and pointer < len(array):
            prev = array[pointer]
            pointer += 1
            cur = array[pointer]
            if prev == cur:
                k += 1
        return array[pointer]

## How this works:
## This works IF repeating values are not counted.
## You first sort the array in reverse order and then
## iterate the array from left to right k times and
## if you see a duplicate, you increment k by one.

## If repeated values are counted, you can return 
## the array at index k instead

## Runtime: O(n) since we need to sort the array then loop 
## through it again
## Memory Usage: O(1) since we reuse the array to find our value