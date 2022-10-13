#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    i64 a, b;
    cin >> a >> b;
    if (a >= b) {
        cout << a - b << '\n';
        return;
    }
    i64 ans = 2E18;
    for (i64 l = 1, r; l <= b - 1; l = r + 1) {
        r = (b - 1) / ((b - 1) / l);
        ans = min(ans, (l + 1) * max(0LL, (b - 1) / l + 1 - a) + l * a - b);
    }
    ans = min(ans, b * a - b);

    assert(ans != 2E18);
    cout << ans << '\n';
    return;
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