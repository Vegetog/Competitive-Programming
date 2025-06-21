import sys
from functools import lru_cache
input = sys.stdin.readline
sys.setrecursionlimit(10 ** 8)

# @lru_cache(maxsize=None)

for _i in range(int(input())):
    a, b = map(int, input().split())
    print('a + b = ',a + b)
