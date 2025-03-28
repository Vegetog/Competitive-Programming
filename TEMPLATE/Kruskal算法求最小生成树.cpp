/*
Kruskal算法求最小生成树
tips:通过并查集、sort+贪心实现
题目链接：https://www.acwing.com/problem/content/description/861/
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;

int p[N];//保存并查集

struct E{
    int a;
    int b;
    int w;
    bool operator < (const E& rhs){//通过边长进行排序
        return this->w < rhs.w;
    }

}edg[N * 2];
int res = 0;

int n, m;
int cnt = 0;
int find(int a){//并查集找祖宗
    if(p[a] != a) p[a] = find(p[a]);
    return p[a];
}
void klskr(){
    for(int i = 1; i <= m; i++)//依次尝试加入每条边
    {
        int pa = find(edg[i].a);// a 点所在的集合
        int pb = find(edg[i].b);// b 点所在的集合
        if(pa != pb){//如果 a b 不在一个集合中
            res += edg[i].w;//a b 之间这条边要
            p[pa] = pb;// 合并a b
            cnt ++; // 保留的边数量+1
        }
    }
}
void solve()
{

    cin >> n >> m;
    for(int i = 1; i <= n; i++) p[i] = i;//初始化并查集
    for(int i = 1; i <= m; i++){//读入每条边
        int a, b , c;
        cin >> a >> b >>c;
        edg[i] = {a, b, c};
    }
    sort(edg + 1, edg + m + 1);//按边长排序
    klskr();
    if(cnt < n - 1) {//如果保留的边小于点数-1，则不能连通
        cout<< "impossible";
    //    return ;
    }else
    cout << res;

}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--){
    	solve();
	}
}