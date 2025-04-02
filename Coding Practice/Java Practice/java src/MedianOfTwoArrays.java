class Solution {
    public static void main(String[] args){
        int[] nums1 = new int[]{1,3};
        //findMedianSortedArrays();
    }

    //Start from the lowest value in either array and go up until you reach halfway
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int l1 = 0, l2 = 0, prev = 0, cur = 0;
        int len = nums1.length + nums2.length;
        for (int i = 0; i < len / 2 + 1; i++) {
            prev = cur;
            if (l1 == nums1.length || l2 == nums2.length) {
                if (l1 >= nums1.length) {
                    cur = nums2[l2++];
                } else {
                    cur = nums1[l1++];
                }
            } else if (nums1[l1] > nums2[l2]) {
                cur = nums2[l2++];
            } else {
                cur = nums1[l1++];
            }
        }
        //System.out.println("Prev: " + prev + "/nCur: " + cur);

        if (len % 2 == 0)
            return (cur + prev) / 2.0;
        else
            return cur;
    }
}