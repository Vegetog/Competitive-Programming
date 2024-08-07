#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h" 
#endif

#define int long long
#define new _MY_NEW_

using namespace std;
using ll = long long;
using PII = array<int, 2>;

constexpr long long INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

void SINGLE_TEST() 
{
    int y;cin>>y;
    if(y%400==0 || y%100!=0 && y%4==0){
        cout<<366<<'\n';
    }else{
        cout<<365<<'\n';
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
