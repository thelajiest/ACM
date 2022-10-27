/*你的愛會將我灌醉*/
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int INF = 1e18;
const int MAX_N = 1e5 + 7;
int a[MAX_N];
int T, n;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            a[i] = abs(a[i] - a[i - 1]);
        }
        int now = 0;
        for (int i = 1; i < n; ++i) {
            now = gcd(now, a[i]);
        }
        cout << "Case " << cas << ": ";
        int ans = INF;
        if (!now) {
            cout << "0\n";
        } else {
            if (now != 1) {
                if (a[0] % now) {
                    ans = min(ans, now - a[0] % now);
                } else {
                    ans = 0;
                }
            }
            for (int i = 2; i * i <= now; ++i) {
                if (now % i) continue;
                if (a[0] % i) {
                    ans = min(ans, i - a[0] % i);
                } else {
                    ans = 0;
                }
                if (ans % (now / i)) {
                    ans = min(ans, now / i - a[0] % (now / i));
                } else {
                    ans = 0;
                }
            }
            if (ans >= INF) {
                cout << "-1\n";
            } else {
                cout << ans << "\n";
            }
        }
    }
    return 0;
}