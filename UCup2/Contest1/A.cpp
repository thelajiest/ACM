#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 1E3 + 100;

int T;
int n, m;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        int mx = m, mi = n / (n - m + 1);
        cout << mx << ' ' << mi << '\n';
    }

    return 0;
}