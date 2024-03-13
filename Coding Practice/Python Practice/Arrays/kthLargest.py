## Description:
## Given an int array and an integer, k, find the kth largest
## integer in the array

def kthLargest(array, k):
    ## base case
    if len(array) < k:
        return 0
    if k < 0:
        return 0
    if k < 1:
        return array[0]

    array.sort(reverse=True)
    p = 0
    k -= 1
    while k > 0:
        prev = array[p]
        p += 1
        if p > len(array)-1:
            return -1
        while prev == array[p]:
            p += 1
            if p > len(array)-1:
                return -1
        k -= 1
    return array[p]


if __name__ == '__main__':
    a1 = input("Enter numbers separated by spaces for array:")
    l1 = list(map(int, a1.split(' ')))
    k = int(input("kth largest value to look for:"))
    result = kthLargest(l1, k)
    print(result)
