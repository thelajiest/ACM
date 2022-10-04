#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAX_N = 1e6 + 7;
vector<int> a[MAX_N], f[MAX_N];
int n, m;

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    a[0].resize(m + 1), f[0].resize(m + 1);
    for (int i = 1; i <= n; ++i) {
        a[i].emplace_back(0);
        f[i].emplace_back(0);
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j) {
            int t = 0;
            if (s[j - 1] == '1') t = 1;
            a[i].emplace_back(t);
            f[i].emplace_back(0);
        }
    }
    // cerr << a[1].size() << endl;
    for (int i = 0; i <= n; ++i) f[i][0] = 1;
    for (int i = 0; i <= m; ++i) f[0][i] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int t = max(f[i - 1][j], max(f[i][j - 1], f[i - 1][j]));
            int mul1 = a[i - 1][j] & ((t / f[i - 1][j]) & 1);
            int mul2 = a[i][j - 1] & ((t / f[i][j - 1]) & 1);
            int mul3 = a[i - 1][j - 1] & ((t / f[i - 1][j - 1]) & 1);
            int odd = mul1 ^ mul2 ^ mul3;
            if (odd) {
                t <<= 1ll;
            }
            if (a[i][j]) {
                a[i][j] = (t & 1) ^ odd;
            } else {
                a[i][j] = 0;
            }
            f[i][j] = t;
            // cout << i << ", " << j << "=" << f[i][j] << ", " << a[i][j] <<
            // endl;
        }
    }
    cout << f[n][m] << "\n";
    return 0;
}
