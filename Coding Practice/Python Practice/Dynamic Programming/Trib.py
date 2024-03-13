class Solution(object):
    @staticmethod
    def tribonacci(n):
        memo = [0] * (n+1)

        def trib(m):
            ## Base cases: tri(0) = 0, tri(1,2) = 1
            if m < 2:
                return 0
            if m == 3:
                return 1
            ## if value is not memoized, memoize it
            if memo[m] == 0:
                memo[m] = trib(m - 1) + trib(m - 2) + trib(m - 3)
            return memo[m]

        return trib(n)


if __name__ == '__main__':
    solution = Solution()
    num = int(input("Enter Tribonacci number: "))
    result = solution.tribonacci(num)
    print(result)
