#include<iostream>
using namespace std;

int median_of_small_group(int* arr, int len){

    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j]) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    int mid = len/2;
    return arr[mid];
}


int median_of_medians(int* arr, int arr_len){
    // cout<<"mom:"<<arr_len<<endl;
    if(arr_len <= 5){
        return median_of_small_group(arr, arr_len);
    }
    int reduce_len = arr_len/5 + (arr_len%5 != 0);
    int *reduced_arr = new int[reduce_len];
    int r=0;
    for(int i=0;i<arr_len;i+=5){
        int m = median_of_small_group(arr+i, min(5, arr_len - i));
        reduced_arr[r++] = m;
    }
    int mid =  median_of_medians(reduced_arr, r);
    delete [] reduced_arr;
    return mid;
}

// int partition(int* arr, int n, int pivot){
//     int L=0, R=n-1;
//     while(L<R){
//         while(L<R and arr[L]<pivot )L++;
//         while(L<R and arr[R]>pivot )R--;
//         if(L<R){
//             swap(arr[L], arr[R]);
//             L++;
//             R--;
//         }
//     }
//     return min(L,R);
// }
int* tmp;
int partition(int* arr, int n, int pivot){
    int L = 0, R = n-1;
    for(int i=0;i<n;i++){
        if(arr[i]<pivot){
            tmp[L++] = arr[i];
        }
        else if(arr[i]> pivot){
            tmp[R--] = arr[i];
        }
    }
    for(int i=L;i<=R;i++)tmp[i] = pivot;
    for(int i=0;i<n;i++)arr[i] = tmp[i];
    return L;
}

// int partition(int* arr, int n, int pivot){
//     int L=0, R=n-1;
//     int i=0;
//     while(i<=R){
//         if(arr[i] == pivot)i++;
//         else if (arr[i]<pivot){
//             swap(arr[L], arr[i]);
//             L++;
//             i++;
//         }
//         else{
//             swap(arr[i], arr[R]);
//             R--;
//         }
//     }
//     return L;
// }


int get_kth_by_dc(int* arr, int L, int R, int k){ 
    // cout<<L<<","<<R<<", k="<<k<<endl;
    if(R-L <= 1)return arr[L];
    int pivot = median_of_medians(arr+L, R-L);
    int i = partition(arr+L, R-L, pivot);
    int ir = i;
    while(L+ir+1<R and arr[L+ir+1]<= pivot)ir++;

    // for(int i=L;i<R;i++)cout<<arr[i]<<" ";cout<<endl;
    // cout<<"\tpivot:"<<pivot<<",\t "<<i<<','<<ir<<endl;

    if(i+1 <= k and k<= ir+1){
        // cout<<"return pivot\n";
        return pivot;
    }


    // for(int i=L;i<R;i++)cout<<arr[i]<<" ";cout<<endl;
    // cout<<"\tpivot:"<<pivot<<",\t "<<i<<','<<ir<<endl;

    if(k<i+1){
        return get_kth_by_dc(arr, L, L + i, k);
    }
    else{
        return get_kth_by_dc(arr, L+ir+1, R, k-ir-1);
    }
}


int main(){
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        int *arr = new int[n];
        tmp = new int[n+5];
        for(int i=0;i<n;i++)cin>>arr[i];
        cout << get_kth_by_dc(arr, 0, n, n-k+1) << endl <<endl;
        delete [] arr;
    }
    return 0;
}