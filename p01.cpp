#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, l;
    cin >> n >> k >> l;
    vector<int> boundary(n+1), steps(l), terminals;
    for (int i=0, x; i<k; ++i) {
        cin >> x;
        boundary[x-1] ^= 1;
        boundary[x] ^= 1;
    }
    for (int &s : steps) cin >> s;
    sort(steps.begin(), steps.end());
    steps.erase(unique(steps.begin(), steps.end()), steps.end());
    for (int i=0; i<=n; ++i)
        if (boundary[i]) terminals.push_back(i);
    int t=terminals.size();
    const int inf=100000000;
    vector<vector<int>> cost(t, vector<int>(t));
    for (int i=0; i<t; ++i) {
        vector<int> dist(n+1, inf);
        queue<int> q;
        q.push(terminals[i]);
        dist[terminals[i]]=0;
        while (!q.empty()) {
            int u=q.front();
            q.pop();
            for (int s : steps)
                for (int v : {u-s,u+s})
                    if (v>=0 && v<=n && dist[v]==inf) {
                        dist[v]=dist[u]+1;
                        q.push(v);
                    }
        }
        for (int j=0; j<t; ++j) cost[i][j]=dist[terminals[j]];
    }
    vector<int> dp(1<<t, inf);
    dp[0]=0;
    for (int mask=1; mask<(1<<t); ++mask) {
        if (__builtin_parity((unsigned)mask)) continue;
        int i=__builtin_ctz(mask), rest=mask^(1<<i);
        for (int bits=rest; bits; bits &= bits-1) {
            int j=__builtin_ctz(bits);
            dp[mask]=min(dp[mask], cost[i][j]+dp[rest^(1<<j)]);
        }
    }
    cout << (dp.back()==inf ? -1 : dp.back()) << '\n';
}
