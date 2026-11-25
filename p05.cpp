#include <bits/stdc++.h>
using namespace std;
struct Node {
    array<int,26> next{};
    int word=-1;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    string text;
    cin >> n >> text >> m;
    vector<string> words(m);
    size_t capacity=1;
    for (auto &w : words) { cin >> w; capacity+=w.size(); }
    vector<Node> trie;
    trie.reserve(capacity);
    trie.emplace_back();
    for (int i=0; i<m; ++i) {
        int u=0;
        for (auto it=words[i].rbegin(); it!=words[i].rend(); ++it) {
            int c=tolower(*it)-'a';
            if (!trie[u].next[c]) {
                trie[u].next[c]=trie.size();
                trie.emplace_back();
            }
            u=trie[u].next[c];
        }
        trie[u].word=i;
    }
    vector<int> used(n+1,-1);
    used[0]=m;
    for (int i=0; i<n; ++i) {
        if (used[i]<0) continue;
        int u=0;
        for (int j=i; j<n; ++j) {
            u=trie[u].next[text[j]-'a'];
            if (!u) break;
            if (trie[u].word>=0) used[j+1]=trie[u].word;
        }
    }
    vector<int> sentence;
    for (int end=n; end>0;) {
        int w=used[end];
        sentence.push_back(w);
        end-=words[w].size();
    }
    reverse(sentence.begin(),sentence.end());
    for (size_t i=0; i<sentence.size(); ++i)
        cout << (i ? " " : "") << words[sentence[i]];
    cout << '\n';
}
