#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int ans = 0;
        int i = 1, j = 1;
        while (true) {
            if (n < 10 * j) {
                ans += (n - j + 1) * i;
                break;
            } else {
                ans += (10 * j - j) * i;
                i += 1;
                j *= 10;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}