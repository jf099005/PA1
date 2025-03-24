#include<bits/stdc++.h>
using namespace std;

int partition(int* arr, int n, int pivot){
    int L=0, R=n-1;
    while(L<R){
        while(L<R and arr[L]<pivot )L++;
        while(L<R and arr[R]>pivot )R--;
        if(L<R){
            swap(arr[L], arr[R]);
            L++;
            R--;
        }
    }
    for(int i=0;i<n;i++){
        if(arr[i] == pivot)return i;
    }
    return L;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7};
    partition(arr, 7,5);
    for(int i=0;i<7;i++)cout<<arr[i];
}