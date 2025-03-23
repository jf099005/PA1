#include<iostream>
#include<vector>
#include<queue>
using namespace std;
long long E= 1e9, MOD = 1e10+69;

signed main(){
    typedef pair<int,int> pii;
    int k; cin>>k;
    vector<int>arr[k];
    int n=0;
    
    for(int i=0;i<k;i++){
        int ni;cin>>ni;
        n += ni;
        arr[i] = vector<int>(ni);
        for(int j=0;j<ni;j++)
            cin>>arr[i][j];
    }

    priority_queue<pii, vector<pii> ,greater<pii> > pq;
    int len[k];
    for(int i=0;i<k;i++)len[i] = 0;
    for(int i=0;i<k;i++){
        pq.push(pii(arr[i][0], i));
        len[i] ++ ;
    }
    long long ans[n], L=0;
    // cout<<"start\n";
    while(pq.size()){
        pii x = pq.top();
        pq.pop();
        int v = x.first, idx = x.second;
        ans[L++] = v;
        if(len[idx]<arr[idx].size())
            pq.push( pii(arr[idx][ len[idx] ], idx) );
        len[idx]++;
    }
    long long sol;
    long long sol_dec = 0;
    long long last = 0;
    int m= 100000;
    for(int i=0;i<n;i++){
        sol = (sol_dec*E%MOD)*m%MOD + last * E%MOD + ans[i];
        // sol = sol*E + ans[i];
        sol %= MOD;
        // cout<<i<<":"<<sol<<endl;
        sol_dec = sol/m;
        last = sol % m;
    }
    cout<< sol<<endl;
    return 0;
}