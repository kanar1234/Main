class MostWater {
    public int maxArea(int[] height) {
        int l = 0;
        int r = height.length-1;
        int maxArea = 0;
        while(l < r){
            // System.out.println("height[l] = " + height[l] + " height[r] = " + height[r] + " Area = " + maxArea);
            maxArea = Math.max(Math.min(height[r], height[l]) * (r-l), maxArea);
            if(height[r] > height[l]) {
                l++;
            } else{
                r--;
            }
        }

        return maxArea;
    }
}