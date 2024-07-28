#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;

const ll inf = 2e18 + 10;
const int mod = 998244353;
const int MAX = 2e5 + 10;

ll n;
string str;
int tptime(string s,string zc){
    int idx=0,cnt=0;
    //zc为子串,cnt为次数，idx为下标
    //s.find如果没找到返回s.npos
    /*
    position = s.find_first_of(flag);//找第一次出现
    
    printf("s.find_first_of(flag) is :%d\n",position);

    position = s.find_last_of(flag);//最后一次出现

    printf("s.find_last_of(flag) is :%d\n",position);
    */
    while((idx=s.find(zc,idx))<s.length()){
        cnt++;
        idx++;
    }
    if(cnt==2) return 1;
    return 0;
}
int rd(int a,int b){
    srand((unsigned)time(NULL));
    return (rand() % (b-a+1))+a;
}
bool solve()
{
    // srand((unsigned)time(NULL));
    // (rand() % (b-a+1))+a
    ll k=rd(1,20);
    
    string s;
    for(int i=1;i<=rd(1,10);i++){
        s+="0";
    }
    for(int i=1;i<=rd(1,10);i++){
        s+="1";
    }
//	ll k;cin>>k;
	ll js=0;
	sort(s.begin(),s.end());
	do{
		if (Solve(k,s)){

        } //cout<<"AC";
        else {
            cout<<"WAAAAAAAAAAAA";
            cout<<"*"<<s<<"*";
            return 0;
            break;
            }


    //    cout<<'\n';

		
	}while(next_permutation(s.begin(),s.end()));
    return 1;
}
int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0); cout.tie(0);
    ll T = 1;
    cin >> T;
    while(T --) {
        if(!solve()) return 0;
    }
    return 0;
}