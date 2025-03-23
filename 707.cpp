#include<iostream>
#include<vector>
using namespace std;


int partition(int* arr, int n, int L, int R, int p){
    if(p==0){
        int i=L;
        int x = arr[L];
        for(int j=L+1;j<=R;j++){
            if( arr[j] <= x ){
                i++;
                swap(arr[i],arr[j]);
            }
        }
        swap(arr[L], arr[i]);
        return i;
    }
    if(p==1){
        int x = arr[R];

        int i=L-1;
        for(int j=L;j<R;j++){
            if( arr[j] <= x ){
                i++;
                swap(arr[i],arr[j]);
            }
        }
        i++;
        swap(arr[R], arr[i]);
        return i;
    }
    int mid = (L+R)/2;
    int x = arr[mid];
    int i=L;
    for(int j=L;j<=R;j++){
        if(arr[j]<=x and j!=mid){
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[mid]);
    i++;
    return i;
}

void quicksort(int* arr, int n, int L, int R, int p){
    if(L>=R)return;
    int mid = partition(arr, n, L, R, p);
    cout<<L<<" "<<R<<" "<<arr[mid]<<endl;
    for(int i=0;i<n;i++)cout<<arr[i]<<' ';
    cout<<endl;
    quicksort(arr, n, L, mid-1, p);
    quicksort(arr, n, mid+1, R, p);
    return;
}

int main(){
    int T;cin>>T;
    while(T--){
        int n, p;cin>>n>>p;
        int arr[n];
        for(int i=0;i<n;i++)cin>>arr[i];
        quicksort(arr, n, 0, n-1, p);
        for(int i=0;i<n;i++)cout<<arr[i]<<" ";
        cout<<endl;
    }
}