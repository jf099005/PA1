#include<iostream>
#include<vector>
#include<queue>
using namespace std;
long long E= 1e9, MOD = 1e10+69;

const int N_MAX = 5e6+10;
const int K_MAX = 1e6+10;
int arr[N_MAX];
int que_L[K_MAX], que_R[K_MAX];
int tmp[N_MAX];
void merge(int* arr, int idx_L, int idx_R, int L, int R){
    // cout<<"merge of idx "<<idx_L<<","<<idx_R<<", interval:"<<L<<","<<R<<"  |  ";
    // for(int i=L;i<R;i++)cout<<arr[i]<<" ";cout<<endl;

    if(idx_R <= idx_L)return;
    int idx_mid = (idx_L + idx_R)/2;
    int mid = que_R[idx_mid];
    
    merge(arr, idx_L, idx_mid,   L,     mid);
    merge(arr, idx_mid+1, idx_R, mid, R);

    int cur_L = L, cur_R = mid;
    int t = L;
    while(cur_L<mid and cur_R<que_R[idx_R]){
        if(arr[cur_L] < arr[cur_R]){
            tmp[t++] = arr[cur_L++];
        }
        else{
            tmp[t++] = arr[cur_R++];
        }
    }

    // cout<<"\t out of the merge, t="<<t<<": "<<cur_L<<"/"<<cur_R<<endl;
    // for(int i=L;i<R;i++)cout<<tmp[i]<<" ";cout<<endl;

    while(cur_L<mid)tmp[t++] = arr[cur_L++];
    while(cur_R<que_R[idx_R])tmp[t++] = arr[cur_R++];
    
    // cout<<"\t at the end, t="<<t<<": "<<cur_L<<"/"<<cur_R<<endl<<"\t\t";
    // for(int i=L;i<R;i++)cout<<tmp[i]<<" ";cout<<endl;

    for(int i= que_L[idx_L]; i<que_R[idx_R];i++ )
        arr[i] = tmp[i];


    // cout<<"\t "<<L<<","<<R<<"  |  "<<que_L[idx_L]<<","<<que_R[idx_R]<<endl;
    // cout<<"\t sol of"<<L<<","<<R<<":";
    // for(int i=L;i<R;i++)cout<<arr[i]<<" ";cout<<endl;


    return;
}

signed main(){
    int k;cin>>k;
    int n=0;
    for(int i=0;i<k;i++){
        int ni;cin>>ni;
        que_L[i] = n;
        for(int j=0;j<ni;j++){
            cin>>arr[n+j];
        }
        n += ni;
        que_R[i] = n;
    }  
    merge(arr, 0, k-1, 0,n);

    // for(int i=0;i<n;i++)cout<<arr[i]<<" ";
    // cout<<endl;

    long long sol;
    long long sol_dec = 0;
    long long last = 0;
    int m= 100000;
    for(int i=0;i<n;i++){
        sol = (sol_dec*E%MOD)*m%MOD + last * E%MOD + arr[i];
        // sol = sol*E + ans[i];
        sol %= MOD;
        // cout<<i<<":"<<sol<<endl;
        sol_dec = sol/m;
        last = sol % m;
    }
    cout<< sol<<endl;
    return 0;
}