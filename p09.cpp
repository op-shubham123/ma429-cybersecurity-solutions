#include <bits/stdc++.h>
#include "timeline.hpp"
using namespace std;
struct Contact { Edge edge; int first, day; };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q,k;
    cin >> n >> q >> k;
    vector<Contact> contacts;
    vector<int> people, dayStart{0};
    for (int i=0; i<q; ++i) {
        int type;
        cin >> type;
        if (type==1) {
            Edge e;
            cin >> e.u >> e.v;
            contacts.push_back({e,(int)people.size(),(int)dayStart.size()-1});
        } else if (type==2) {
            int u;
            cin >> u;
            people.push_back(u);
        } else dayStart.push_back(people.size());
    }
    Timeline time(people.size());
    for (auto c : contacts) {
        int expiry=c.day+k;
        int end=expiry<(int)dayStart.size() ? dayStart[expiry] : (int)people.size();
        time.insert(c.first,end,c.edge);
    }
    RollbackDSU state(n,false);
    time.run(state,[&](int i,const RollbackDSU &s) {
        cout << s.size(people[i]) << '\n';
    });
}
