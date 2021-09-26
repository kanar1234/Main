## Description:
## Given two linked lists with non-negative, single digit, integers 
## stored in reverse order,
## i.e. 123 is stored as 3->2->1 
## add them and return the sum as a linked list

## Example:
## l1 = [1,2,3], l2 = [2,3,4]
## out = [3,5,7]

## this is why it's stored in reverse order
## l1 = [1], l2 = [8,9,9]
## out = [9,0,0]

## also remember these cases
## l1 = [1], l2 = [9,9,9]
## out = [1,0,0,0]

## Definition for singly-linked list.
## class ListNode(object):
##     def __init__(self, val=0, next=None):
##         self.val = val
##         self.next = next
class Solution(object):
    def addTwoNumbers(self, l1, l2):
        out = prev = l1
        remainder = 0
        while l1 or l2:
            if l1 and l2:
                l1.val = total % 10
                remainder = total/10
                prev = l1
                l1 = l1.next
                l2 = l2.next
            elif l2:
                prev.next = l2
                l2 = prev.next
                while remainder > 0:
                    if l2:
                        total = l2.val + remainder
                        l2.val = total%10
                        remainder = total/10
                        prev = l2
                        l2 = l2.next
                    else:
                        prev.next = ListNode(remainder)
                        remainder = 0
                break
            else: ##if l1
                while remainder > 0:
                    if l1:
                        total = l1.val + remainder
                        l1.val = total%10
                        remainder = total/10
                        prev = l1
                        l1 = l1.next
                    else:
                        prev.next = ListNode(remainder)
                        remainder = 0
                break
        if remainder > 0:
            prev.next = ListNode(remainder)
        return out

## Notes:
## I originally had it create a new linked list, but I figured I could
## improve it by just modifying the first linked list to save memory but
## doing so made me need to create a pointer to the previous value so I
## could append new values if I reach the end of the linked list

## How it works:
## We need to move our pointers at the same time, so we first check
## if l1 or l2 exists
## if l1 and l2 exists: we add the two values with the remainder
## and modify l1 to be the the sum%10 and then move our pointer
## to the next value in both of the linked lists
## if only l1 exists: we only need to check if there are remainders, 
## otherwise we basically return that list
## if only l2 exists: we need to append nodes until we reach the end of l2
## also we do not need to move l1 anymore since we've reached its end

## Runtime: O(n) where the upper bound is the max length of l1 and l2
## Memory: O(1) since we reuse l1 instead of creating a new linked list