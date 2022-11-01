#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n);
    for (auto& it : a) cin >> it;
    auto [mn, mx] = minmax_element(a.begin(), a.end());
    i64 ans = numeric_limits<i64>::max();

    for (auto it = a.begin(); it != a.end(); it++) {
        if (it == mn || it == mx) continue;
        ans = min(ans, abs(*it - *mn) + abs(*it - *mx));
    }

    cout << ans << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}