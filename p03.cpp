#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const string alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int base=alphabet.size(), nodes=base*base;
    int id[128]={};
    for (int i=0; i<base; ++i) id[(int)alphabet[i]]=i;
    vector<vector<int>> out(nodes);
    vector<int> balance(nodes);
    int n, start=0;
    cin >> n;
    for (int i=0; i<n; ++i) {
        string s;
        cin >> s;
        start=id[(int)s[0]]*base+id[(int)s[1]];
        int end=id[(int)s[1]]*base+id[(int)s[2]];
        out[start].push_back(end);
        ++balance[start];
        --balance[end];
    }
    int plus=0, minus=0;
    for (int i=0; i<nodes; ++i) {
        if (abs(balance[i])>1) { cout << "NO\n"; return 0; }
        if (balance[i]==1) { start=i; ++plus; }
        if (balance[i]==-1) ++minus;
    }
    if (plus!=minus || plus>1) { cout << "NO\n"; return 0; }
    vector<int> stack{start}, path;
    while (!stack.empty()) {
        int u=stack.back();
        if (out[u].empty()) {
            path.push_back(u);
            stack.pop_back();
        } else {
            stack.push_back(out[u].back());
            out[u].pop_back();
        }
    }
    if ((int)path.size()!=n+1) { cout << "NO\n"; return 0; }
    reverse(path.begin(),path.end());
    cout << "YES\n" << alphabet[path[0]/base];
    for (int u : path) cout << alphabet[u%base];
    cout << '\n';
}
