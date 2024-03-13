class Solution(object):
    def fib(self, n):
        memo = [0] * (n + 1)
        if n < 0:
            return 0
        if n == 0 or n == 1:
            return 1

        if memo[n] == 0:
            memo[n] = self.fib(n - 1) + self.fib(n - 2)

        return memo[n]


if __name__ == '__main__':
    solution = Solution()
    num = int(input("Enter Fib Number:"))
    result = solution.fib(num)
    print(result)
