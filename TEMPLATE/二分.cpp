#include<bits/stdc++.h>
using namespace std;
int a[2000005];
//找后继 
int bin_search(int *a,int n,int x){
	int left=0,right=n;
	while(left<right){
		int mid=(left+right)>>1;
		if(a[mid]>=x) right=mid;
		else  left =mid+1;
	}
	return left;
} 
//找前驱 
int bin_search2(int *a,int n,int x){
	int left=0,right=n;
	while(left<right){
		int mid=(left+right+1)>>1;
		if(a[mid]<=x) left=mid;
		else  right =mid-1;
	}
	return left;
}
int main()
{
	//
	int k;
	//lower_bound和 upper_bound,返回值为下标 
	int pos1=lower_bound(num,num+6,k)-num;    //返回数组中第一个大于或等于被查数的值 
	int pos2=upper_bound(num,num+6,k)-num;    //返回数组中第一个大于被查数的值
	int pos3=lower_bound(num,num+6,k,greater<int>())-num;  //返回数组中第一个小于或等于被查数的值 
	int pos4=upper_bound(num,num+6,k,greater<int>())-num;  //返回数组中第一个小于被查数的值
	/*
	vector找不到的时候是返回最后一个下标加1 的一个数
	数组则返回0
	*/
}


