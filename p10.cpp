#include <bits/stdc++.h>
using namespace std;
int query(int count,int room,int n) {
    cout << "? " << count << ' ' << room << endl;
    int value;
    if (!(cin >> value) || value<1 || value>n) exit(0);
    return value;
}
int main() {
    int n;
    if (!(cin >> n)) return 0;
    int c=query(n,1,n);
    int r=c==n ? 1 : query(n-c,1,n);
    cout << "! " << c << ' ' << r << endl;
}
