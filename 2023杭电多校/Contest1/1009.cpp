#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n, m, d;
        cin >> n >> m >> d;
        cout << (n * (d - 1) > m ? "No" : "Yes") << '\n';
    }

    return 0;
}