#include<bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int,2>;
using namespace std;
const ll INF = 2E18+10;
#define inr(ITEM,a,b) (a<=ITEM&&ITEM<=b)
#ifndef ONLINE_JUDGE
    #include ".debug.h"
    #define EL std::cout<<"\n";
    #define COUT(ITEM) std::cout<<#ITEM<<"="<<ITEM<<'\n';
    #define CERR(ITEM) std::cerr<<#ITEM<<"="<<ITEM<<'\n';
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y; }};
const int N = 2E6 + 10;
long long merge_and_count(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;    // 左子数组的起始索引
    int j = mid + 1; // 右子数组的起始索引
    int k = left;    // 合并后数组的起始索引
    long long inv_count = 0; // 逆序对计数

    // 合并两个子数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid + 1 - i); // 统计逆序对
        }
    }

    // 复制剩余的左子数组元素
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // 复制剩余的右子数组元素
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 将排序好的数据复制回原数组
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

long long merge_sort_and_count(vector<int>& arr, vector<int>& temp, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = (left + right) / 2;

        // 分别对左右子数组进行排序并统计逆序对
        inv_count += merge_sort_and_count(arr, temp, left, mid);
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right);

        // 合并两个子数组并统计跨子数组的逆序对
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }
    return inv_count;
}

long long count_inversions(vector<int>& arr) {
    vector<int> temp(arr.size());
    return merge_sort_and_count(arr, temp, 0, arr.size() - 1);
}

void SINGLE_TEST()
{
    int n;cin>>n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    auto c=a;
    sort(c.begin(),c.end());
    auto d=b;
    sort(d.begin(),d.end());
    if(c!=d){
        cout<<"NO\n";
        return;
    }
    int n1=count_inversions(a);
    int n2=count_inversions(b);
    if((n1%2==n2%2)){
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);

    int SAMPLES = 1;
	cin>>SAMPLES;
    while(SAMPLES--) SINGLE_TEST();
}
