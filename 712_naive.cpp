#include<algorithm>
#include<iostream>
using namespace std;
int main(){
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        int *arr = (int*)malloc(n*sizeof(int));
        for(int i=0;i<n;i++)cin>>arr[i];
        sort(arr,arr+n);
        cout<<arr[n-k]<<endl;
    }
    return 0;
}