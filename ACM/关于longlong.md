#关于longlong

1.
https://ac.nowcoder.com/acm/contest/60282/D
在超过int范围下的最短路时，初始化最短路不能用0x3f，要用INF

2.
string.size()的返回值是int，
如在相乘是要用(ll)string.size()转化为ll

3.
题目链接：https://codeforces.com/contest/1846/problem/E2
对于jia的爆longlong问题的处理需要注意，提前处理，不要等爆longlong了再处理
这里可以采用除的方法 ：INF/k<jia