#include<iostream>
#include<algorithm>
#include<stdlib.h>
using namespace std;
int median_of_small_group(int* arr, int len){
    sort(arr, arr+len);
    int mid = len/2;
    return arr[mid];
}


int median_of_medians(int* arr, int arr_len){

    if(arr_len <= 5){
        return median_of_small_group(arr, arr_len);
    }
    int reduce_len = arr_len/5 + (arr_len%5 != 0);
    int *reduced_arr = (int*)malloc(reduce_len*sizeof(int));
    int r=0;
    for(int i=0;i<arr_len;i+=5){
        int m = median_of_small_group(arr+i, min(5, arr_len - i));
        reduced_arr[r++] = m;
    }

    // cout<<"\t\t in median, reduced: ";
    // for(int i=0;i<r;i++)cout<<reduced_arr[i]<<" ";cout<<endl;

    return median_of_medians(reduced_arr, r);
}

int partition(int* arr, int n, int pivot){
    int L=0, R=n-1;
    while(L<R){
        while(L<R and arr[L]<pivot )L++;
        while(L<R and arr[R]>pivot )R--;
        if(L<R){
            swap(arr[L], arr[R]);
        }
    }
    for(int i=0;i<n;i++){
        if(arr[i] == pivot)return i;
    }
}

int get_kth_by_dc(int* arr, int L, int R, int k){ // [L,R)
    // cout<<"recurrent :"<<L<<","<<R<<",k="<<k<<endl;
    // system("pause");

    if(R-L == 1)return arr[L];
    int pivot = median_of_medians(arr+L, R-L);
    // cout<<"\t medium:"<< pivot<<endl;
    int i = partition(arr+L, R-L, pivot);

    // cout<<"\t after partition:";
    // for(int j=L;j<R;j++)cout<<arr[j]<<" ";
    // cout<<endl;

    if(k==i+1)return arr[L+i];
    if(k<=i){
        // cout<<"\t call left:"<<L<<","<<i<<endl;
        return get_kth_by_dc(arr, L, L + i, k);
    }
    else{
        // cout<<"\t call right:"<<i+1<<","<<R<<endl;
        return get_kth_by_dc(arr, L+i+1, R, k-i-1);
    }
}

int main(){
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        int *arr = (int*)malloc(n*sizeof(int));
        for(int i=0;i<n;i++)cin>>arr[i];
        cout << get_kth_by_dc(arr, 0, n, n-k+1) << endl <<endl;
    }
    return 0;
}