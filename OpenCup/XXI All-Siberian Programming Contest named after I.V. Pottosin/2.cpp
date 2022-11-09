#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    i64 p, q, a, b;
    cin >> p >> q >> a >> b;

    i64 l = 1, r = 1E9;

    auto check = [&](int x) -> bool {
        i64 org = q * (b + x) * (100 - p);
        i64 now = p * b * (100 - q) * (1 + a * x);
        return org <= now;
    };
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }

    if (check(l)) {
        cout << l << '\n';
    } else
        cout << -1 << '\n';
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