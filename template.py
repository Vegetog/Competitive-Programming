import sys
from functools import lru_cache

input = sys.stdin.readline
sys.setrecursionlimit(10 ** 9)

@lru_cache(maxsize=None)

def Gura():
    a, b = map(int, input().split())
    print('a + b = ',a + b)


if __name__ == '__main__':
    Gawr = 1
    Gawr = int(input())
    for _i in range(Gawr):
        Gura()
