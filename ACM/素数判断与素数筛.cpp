#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;
typedef pair<int,int> PII;

bool isprime(int n){//***判断是否为素数***
    if(n < 2) return false;
    for(int i = 2;i <= n / i;i ++){ 
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
//***埃氏筛***
bool st[N];
ll primes[N];
ll cnt;
void get_primes1(ll n){//埃氏筛
    for(int i=2;i<=n;i++){
        if(!st[i]){
            primes[cnt++]=i;
            for(int j=i*2;j<=n;j+=i) st[j]=true;//可以用质数就把所有的合数都筛掉；
        }
    }
}

//***线性筛***
//primes数组用来存放质数
int primes[N], cnt;
//st[i], i为质数则为false否则为true
bool st[N];
void get_primes(int n)
{
	cnt=1;
    for(int i = 2; i <= n; i++)
    {
        if(!st[i]) primes[cnt++] = i;
        //假设primes[0]为n最小的质因子,i为最大的因数，
        //易知若primes[i]中i>0,则会进入循环后产生多余的标记。
        for(int j = 1; primes[j] <= n / i; j ++)
        {
            //标记;primes[j]一定是primes[j]*i的最小质因子
            st[primes[j]*i] = true;
            //表明primes[j]一定是i的最小质因子,没有必要再遍历,primes要小于等于i的最小质因子
            //这样能保证每个数遍历一遍,而没有重复
            if(i % primes[j] == 0) break;
        }
    }
    cnt--;
}

void solve()
{
	
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--){
    	solve();
	}
}