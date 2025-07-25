import sys
from functools import lru_cache # @lru_cache(maxsize=None)
input = sys.stdin.readline
sys.setrecursionlimit(10 ** 8)

def str_div(s): # "aaabbbccccaaddd" -> ["aaa", "bbb", "ccccc", "aa", "ddd"]
    from itertools import groupby
    return [''.join(g) for _, g in groupby(s)]
def str_div_sg(s): # "aaabbbccccaaddd" -> ["a", "b", "c", "a", "d"]
    import re
    return re.findall(r'(.)\1*', s)

mod = 10 ** 9 + 7

for _i in range(int(input())):
    a, b = map(int, input().split())
    print('a + b = ',(a + b) % mod)