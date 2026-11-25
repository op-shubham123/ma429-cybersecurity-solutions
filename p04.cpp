#include <bits/stdc++.h>
using namespace std;
struct Edge { long long label; int u,v; };
int root(vector<int>& parent,int u) {
    if (parent[u]<0) return u;
    return parent[u]=root(parent,parent[u]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k;
    cin >> n >> m >> k;
    vector<long long> key(n);
    for (auto &x : key) cin >> x;
    vector<Edge> edges(m);
    for (auto &e : edges) {
        cin >> e.u >> e.v;
        --e.u; --e.v;
        e.label=key[e.u]^key[e.v];
    }
    sort(edges.begin(),edges.end(),[](Edge a, Edge b){return a.label<b.label;});
    const long long mod=1000000007;
    vector<long long> power(max(n,k)+1,1);
    for (int i=1; i<(int)power.size(); ++i) power[i]=2*power[i-1]%mod;
    vector<int> parent(n,-1);
    long long answer=power[k]*power[n]%mod;
    for (int i=0; i<m;) {
        int j=i, components=n;
        while (j<m && edges[j].label==edges[i].label) {
            int a=root(parent,edges[j].u), b=root(parent,edges[j].v);
            if (a!=b) {
                if (parent[a]>parent[b]) swap(a,b);
                parent[a]+=parent[b]; parent[b]=a;
                --components;
            }
            ++j;
        }
        answer=(answer+power[components]-power[n]+mod)%mod;
        for (; i<j; ++i) parent[edges[i].u]=parent[edges[i].v]=-1;
    }
    cout << answer << '\n';
}
