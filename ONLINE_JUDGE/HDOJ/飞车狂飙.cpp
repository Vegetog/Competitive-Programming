#include <bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 2E18 + 10;
#ifdef __clang__
    template <typename T>
    inline int my_lg(T n) {return (n > 0) ? static_cast<int>(log2(n)) : -1;}
    #define __lg my_lg
    #define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
    #include "_debug.h"
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y;}};
const int N = 2E6 + 10;

PII ds[]={{1,0},{0,1},{-1,0},{0,-1}};

void SINGLE_TEST() 
{
    int n;cin>>n;
    string s;cin>>s;
    map<PII,bool> vis;
    int x=0,y=0;
    int tow=0;
    bool ok1=0,ok2=0;
    for(int i=0;i<n;i++){
        if(s[i]=='R'){
            x+=ds[tow][0];
            y+=ds[tow][1];
            tow--;
            if(tow<0)tow+=4;
        }else if(s[i]=='L'){
            x+=ds[tow][0];
            y+=ds[tow][1];
            tow++;
            tow%=4;
        }else{
            x+=ds[tow][0];
            y+=ds[tow][1];
        }
        if(vis[{x,y}]){
            ok1=1;
        }
        vis[{x,y}]=true;
        // cerr<<x<<" "<<y<<" "<<tow<<"\n";
    }
    if(x==0 && y==0 && tow==0){
        ok2=1;
    }
    if(ok1){
        cout<<-1<<"\n";
    }else if(!ok2){
        cout<<0<<"\n";
    }else{
        cout<<1<<"\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
