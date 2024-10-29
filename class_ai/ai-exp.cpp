#include<bits/stdc++.h>
#include "_my_utils.h"
using namespace std;

constexpr int N = 5;
constexpr int MAX = 50;

int n = 6; // 物种个数
vector<int> a(n); // 每个物种的染色体编码

void select_and_copy(){
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=a[i]*a[i];
    }
    vector<double> f(n),pr(n);
    for(int i=0;i<n;i++){
        f[i]=1.0*a[i]*a[i]/sum;
        if(i==0) 
            pr[i]=f[i];
        else
            pr[i]=f[i]+pr[i-1];
    }
    debug(f);
    vector<int> cnt(n);
    vector<int> b;
    for(int i=0;i<n;i++){
        double fu=static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        b.push_back(a[lower_bound(pr.begin(),pr.end(),fu)-pr.begin()]);
    }
    a=b;
    debug(a);
}

void cross(){
    for(int i = 0; i < n; i += 2){
        if(a[i] % 2 != a[i+1] % 2){
            if(a[i] % 2 == 1){
                a[i] -= 1;
                a[i+1] += 1;
            }else{
                a[i] += 1;
                a[i+1] -= 1;
            }
        }
        if(a[i] % 4 != a[i+1] % 4){
            if((a[i] % 4 == 0 || a[i] % 4 == 1) && (a[i+1] % 4 == 2 || a[i+1] % 4 == 3)){
                a[i] += 2;
                a[i+1] -= 2;
            }else if((a[i] % 4 == 2 || a[i] % 4 == 3) && (a[i+1] % 4 == 0 || a[i+1] % 4 == 1)){
                a[i] -= 2;
                a[i+1] += 2;
            }
        }
        
        // 限制最大值为50
        if (a[i] > 50) a[i] = 50;
        if (a[i+1] > 50) a[i+1] = 50;
    }
}
/*
21 40 19 16 14 21 
23 17 12 42 13 22 
42 42 42 43 23 22 
22 42 43 42 35 43 
35 43 42 42 42 43 
42 42 42 50 42 42 
42 42 42 50 42 42
*/
void mutate(){
    double mutation_rate = 0.05;  // 设置变异概率
    for(int i = 0; i < n; i++){
        if(static_cast<double>(rand()) / RAND_MAX < mutation_rate){
            int p = rng() % 5;  // 随机选择一个位进行变异
            a[i] ^= (1 << p);  // 通过异或操作翻转该位
            
            // 限制最大值为50
            if(a[i] > 50) a[i] = 50;
        }
    }
}

int main(){
    srand(static_cast<unsigned>(std::time(0)));
    // for(int i=0;i<n;i++){
    //     a[i]=rng()%51;
    // }
    a[0]=21;
    a[1]=40;
    a[2]=19;
    a[3]=16;
    a[4]=14;
    a[5]=21;
    debug(a);
    int cnt=0;
    while(find(a.begin(), a.end(), 50) == a.end()&&cnt< 100){
        select_and_copy();
        debug(a);
        cross();
        debug(a);
        mutate();
        cnt++;
        debug(a);
    }
    cout<<"经过"<<cnt<<"轮找到最大值"<<"\n";
}