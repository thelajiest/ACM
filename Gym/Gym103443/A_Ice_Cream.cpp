#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios::sync_with_stdio(false);
    int T, n, a, b;
    cin >> T;
    while (T--) {
        cin >> a >> b >> n;
        int ans = 0;
        ans += 3 * a * (n / (a + b));
        n %= (a + b);
        ans += 3 * min(n, a);
        cout << ans << '\n';
    }
    return 0;
}