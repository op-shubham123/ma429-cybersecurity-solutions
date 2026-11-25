#include <bits/stdc++.h>
#include "timeline.hpp"
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin >> n >> q;
    Timeline time(q);
    map<pair<int,int>,int> open;
    for (int i=0; i<q; ++i) {
        int u,v;
        cin >> u >> v;
        auto key=make_pair(u,v);
        auto it=open.find(key);
        if (it==open.end()) open[key]=i;
        else {
            time.insert(it->second,i,{u,v});
            open.erase(it);
        }
    }
    for (auto [edge,start] : open) time.insert(start,q,{edge.first,edge.second});
    RollbackDSU state(n,true);
    time.run(state,[](int, const RollbackDSU &s) {
        cout << (s.bipartite() ? "YES\n" : "NO\n");
    });
}
