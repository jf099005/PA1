#include<iostream>
using namespace std;
int median_of_small_group(int* arr, int len){

    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;
        while (key < arr[j] && j >= 0) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    int mid = len/2;
    return arr[mid];
}


int median_of_medians(int* arr, int arr_len){

    if(arr_len <= 5){
        return median_of_small_group(arr, arr_len);
    }
    int reduce_len = arr_len/5 + (arr_len%5 != 0);
    int *reduced_arr = (int*)malloc(arr_len*sizeof(int));
    int r=0;
    for(int i=0;i<arr_len;i+=5){
        int m = median_of_small_group(arr+i, min(5, arr_len - i));
        reduced_arr[r++] = m;
    }
    int mid =  median_of_medians(reduced_arr, r);
    delete [] reduced_arr;
    return mid;
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

int get_kth_by_dc(int* arr, int L, int R, int k){ 
    if(R-L == 1)return arr[L];
    int pivot = median_of_medians(arr+L, R-L);
    int i = partition(arr+L, R-L, pivot);

    if(k==i+1)return arr[L+i];
    if(k<=i){
        return get_kth_by_dc(arr, L, L + i, k);
    }
    else{
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
        delete [] arr;
    }
    return 0;
}