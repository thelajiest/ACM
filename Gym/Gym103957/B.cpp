#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;
void solve() {
    i64 n;
    i64 g, p;
    cin >> n >> g >> p;
    vector<i64> v(n);
    for (auto& it : v) cin >> it;

    if (p < n) {
        i64 sum = 0;
        i64 mx = 0;
        for (int i = 0; i < p; i++) {
            mx = max(mx, sum);
            sum = max(0LL, sum + v[i]);
        }
        cout << max(0LL, g - mx) << '\n';
        return;
    }

    i64 l = 0, r = g;
    while (l < r) {
        i64 mid = (l + r) / 2;
        auto check = [&](i64 x) -> bool {
            i64 sum = x;
            for (int i = 0; i < n; i++) {
                sum = max(0LL, sum + v[i]);
            }
            if (sum > x) {
                i64 add = sum - x;
                i128 now = (i128)add * (n / p - 1);
                i128 mx = now;
                for (int i = 0; i < n % p + n; i++) {
                    mx = max<i128>(mx, now);
                    now = max<i128>(0, now + v[i % n]);
                }
                mx = max<i128>(mx, now);

                return x + mx >= g;
            } else {
                i64 mx = 0;
                i64 sum = x;
                for (int i = 0; i < min(2 * n, p); i++) {
                    mx = max(mx, sum);
                    sum = max(0LL, sum + v[i]);
                }
                mx = max(mx, sum);

                return mx >= g;
            }
        };
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}