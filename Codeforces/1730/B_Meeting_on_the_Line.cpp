#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

void solve() {
    int n;
    cin >> n;
    vector<i64> x(n), t(n);
    for (auto&& it : x) cin >> it;
    for (auto&& it : t) cin >> it;
    i64 mx = numeric_limits<i64>::min(), mn = numeric_limits<i64>::max();
    for (int i = 0; i < n; i++) {
        mx = max(mx, x[i] + t[i]);
        mn = min(mn, x[i] - t[i]);
    }
    cout << fixed << setprecision(8);
    cout << 0.5 * (mx + mn) << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}