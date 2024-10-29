#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 3E6 + 10;
constexpr int M = 70;

unordered_map<char,int> id;
int tr[N+1][M];
int cnt[N+1];

void SINGLE_TEST() 
{
    int n,q;
    cin>>n>>q;

    int tot=1;

    for(int i=1;i<=n;i++){
        string s;cin>>s;
        int p=1;
        for(auto c : s){
            if(tr[p][id[c]]==0){
                tr[p][id[c]]=++tot;
            }
            p=tr[p][id[c]];
            cnt[p]++;
        }
    }

    while(q--){
        string t;cin>>t;
        int p=1;
        bool jp=0;
        for(auto c : t){
            if(tr[p][id[c]]==0){
                jp=1;
                break;
            }
            p=tr[p][id[c]];
        }
        if(jp){
            cout<<0<<"\n";
            continue;
        }
        cout<<cnt[p]<<"\n";
    }

    for(int i=0;i<=tot;i++){
        cnt[i]=0;
        for(int j=0;j<M;j++){
            tr[i][j]=0;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    for(char c='a';c<='z';c++){
        id[c]=c-'a';
    }
    for(char c='A';c<='Z';c++){
        id[c]=c-'A'+26;
    }
    for(char c='0';c<='9';c++){
        id[c]=c-'0'+52;
    }

    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}
