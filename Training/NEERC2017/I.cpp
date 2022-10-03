#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("intel.in", "r", stdin);
    freopen("intel.out", "w", stdout);
    int n;
    cin >> n;

    vector<pair<i64, i64>> a(n);
    pair<i64, i64> X, Y;
    X = {numeric_limits<i64>::max(), numeric_limits<i64>::min()};
    Y = X;
    for (auto && [x, y] : a) {
        cin >> x >> y;
        X.first = min(X.first, x);
        X.second = max(X.second, x);
        Y.first = min(Y.first, y);
        Y.second = max(Y.second, y);
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        auto [x, y] = a[i % n];
        auto [xx, yy] = a[i - 1];
        if (x == xx) {
            ans += abs(y - yy);
        }
        if (y == yy) {
            ans += abs(x - xx);
        }
    }

    i64 ans2 = X.second - X.first + Y.second - Y.first;
    ans2 *= 2;
    ans -= ans2;

    cout << ans << endl;
    return 0;
}