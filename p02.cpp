#include <bits/stdc++.h>
using namespace std;
int reply() {
    int value;
    if (!(cin >> value) || value<0) exit(0);
    return value;
}
int main() {
    int tests=reply();
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> upper(1,(1<<29)-1);
    while (tests--) {
        cout << 1 << endl;
        int o=reply();
        int delta;
        if (o==0) delta=1;
        else if (o>1) delta=2;
        else delta=2*upper(rng)+1;
        cout << 0 << ' ' << delta << endl;
        int r=reply(), bit;
        if (o==0) bit=r&1;
        else if (o>1) bit=((r^o)&2)!=0;
        else {
            // Candidates are r and r XOR delta. Prefer zero, then odd.
            int other=r^delta;
            if (r==0 || other==0) bit=(other==0);
            else bit=(r%2==0);
        }
        cout << bit << endl;
    }
}
