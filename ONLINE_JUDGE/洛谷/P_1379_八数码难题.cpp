#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

const string ed = "123804765";
constexpr int dx[]={0,0,1,-1};
constexpr int dy[]={1,-1,0,0};

void SINGLE_TEST() 
{
    vector<vector<char>> st(3,vector<char>(3));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>st[i][j];
        }
    }

    vector<vector<char>> ed(3,vector<char>(3));
    ed[0][0]='1',ed[0][1]='2',ed[0][2]='3';
    ed[1][0]='8',ed[1][1]='0',ed[1][2]='4';
    ed[2][0]='7',ed[2][1]='6',ed[2][2]='5';

    if(st==ed){
        cout<<"0\n";
        return;
    }

    using M = vector<vector<char>>;
    queue<M> q;
    map<M,int> d;
    map<M,int> vis;
    q.push(st);
    q.push(ed);
    vis[st]=1;
    vis[ed]=2;

    while(!q.empty()){
        auto t=q.front();
        q.pop();
        int x0=-1,y0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(x0==-1&&t[i][j]=='0'){
                    x0=i,y0=j;
                    break;
                }
            }
        }
        for(int i=0;i<4;i++){
            auto nt=t;
            int nx=x0+dx[i],ny=y0+dy[i];
            if(nx>=0&&nx<3&&ny>=0&&ny<3){
                swap(nt[x0][y0],nt[nx][ny]);
                if(vis[nt]==vis[t]) continue;
                if(vis[t]+vis[nt]==3){
                    cout<<d[t]+d[nt]+1<<"\n";
                    return;
                }
                vis[nt]=vis[t];
                d[nt]=d[t]+1;
                q.push(nt);
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}
