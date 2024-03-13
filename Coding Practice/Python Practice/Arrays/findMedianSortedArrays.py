## Description:
## Given two arrays, find the median of the two arrays
def findMedianSortedArrays(nums1, nums2):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :rtype: float
    """
    print("test")
    #combines the two arrays
    if not nums1 and not nums2:
        return 0

    merged = nums1 + nums2
    merged.sort()
    length = len(nums1)+len(nums2)
    if length%2 == 0:
        return (merged[length//2] + merged[length//2-1])//2.0
    return merged[length//2]

## How this works:
## We merge the array then sort it 
## Now we find the median which is always going
## to be the value at the center of the array
## for even lengths, the median is at index length/2
## for odd lengths, the median is the average of the two
## indices in the the center of the array

## Runtime: O(n+m) where n and m are the lengths of the array
## sorting is an O(n) runtime but since we are sorting a merged list,
## O(n) turns into O(n+m)
## The rest of the function uses O(1) runtime so it does not affect
## the overall runtime

class Solver:
    pass


if __name__ == '__main__':
    a1 = input("Enter numbers separated by a space for first array: ")   # takes the whole line of n numbers
    l1 = list(map(int,a1.split(' ')))
    a2 = input("Enter numbers separated by a space for second array: ")   # takes the whole line of n numbers
    l2 = list(map(int,a2.split(' ')))
    result = findMedianSortedArrays(l1, l2)
    print(result)