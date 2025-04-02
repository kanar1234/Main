class Bits {

    public static void main(String[] args){
        System.out.println(count_one(4));
    }

    static int count_one(int n) {
        int count = 0;
        while(n != 0) {
            n = n&(n-1);
            count++;
        }
        return count;
    }
}