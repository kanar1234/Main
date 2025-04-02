public class BuyAndSellStock {
    public static void main(String[] args){

    }
    public int maxProfit(int[] prices) {
        int lowest = prices[0];
        int max = 0;
        for(int i : prices) {
            if(i < lowest)
                lowest = i;
            max = Math.max(i - lowest, max);
        }
        return max;
    }
}