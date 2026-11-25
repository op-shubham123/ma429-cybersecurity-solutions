#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int mod=1000000007;
    static int ways[101][2501];
    ways[0][0]=1;
    for (int len=1; len<=100; ++len) {
        long long window=0;
        for (int s=0; s<=25*len; ++s) {
            window+=ways[len-1][s];
            if (s>=26) window-=ways[len-1][s-26];
            window=(window+mod)%mod;
            ways[len][s]=window;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        string w;
        cin >> w;
        int sum=0;
        for (char c : w) sum+=c-'a';
        cout << (ways[w.size()][sum]+mod-1)%mod << '\n';
    }
}
