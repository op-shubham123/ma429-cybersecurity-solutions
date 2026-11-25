#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i=1,u,v; i<n; ++i) {
        cin >> u >> v;
        --u; --v;
        graph[u].push_back(v); graph[v].push_back(u);
    }
    vector<vector<int>> parent(n,vector<int>(n,-1)), size(n,vector<int>(n,1));
    vector<vector<pair<int,int>>> byLength(n);
    for (int r=0; r<n; ++r) {
        vector<int> order{r}, depth(n);
        for (int i=0; i<n; ++i) {
            int u=order[i];
            for (int v : graph[u]) if (v!=parent[r][u]) {
                parent[r][v]=u;
                depth[v]=depth[u]+1;
                order.push_back(v);
                if (r<v) byLength[depth[v]].emplace_back(r,v);
            }
        }
        for (int i=n-1; i>0; --i) {
            int u=order[i];
            size[r][parent[r][u]]+=size[r][u];
        }
    }
    vector<vector<long long>> best(n,vector<long long>(n));
    long long answer=0;
    for (const auto &layer : byLength) for (auto [u,v] : layer) {
        long long count=1LL*size[u][v]*size[v][u];
        long long prev=max(best[parent[v][u]][v],best[u][parent[u][v]]);
        best[u][v]=best[v][u]=count+prev;
        answer=max(answer,best[u][v]);
    }
    cout << answer << '\n';
}
