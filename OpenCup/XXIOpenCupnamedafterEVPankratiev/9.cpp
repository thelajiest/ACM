#include <bits/stdc++.h>
// #define int long long
// #define sleepy

using namespace std;

const int MAX_D = 250 + 7;
const int MAX_W = 5e3 + 7;
int w, d, T;
double dp[MAX_W][MAX_D];

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> w >> d;
        double ans = 0;
        for (int j = 0; j < w; ++j) {
            int n, f, m;
            cin >> n >> f >> m;
            dp[0][0] = 1;
            int siz = 0;
            for (int i = 1; i <= n; ++i) {
                for (int k = siz; k >= 0; --k) {
                    for (int ff = 1; ff <= f; ++ff) {
                        dp[i][k + ff] += dp[i - 1][k] * 1.0 / f;
                    }
                }
                siz += f;
            }
            double now = 0;
            for (int k = max(d - m, 0); k <= siz; ++k) {
                now += dp[n][k];
            }
            ans = max(ans, now);
            for (int i = 0; i <= n; ++i) {
                for (int k = 0; k <= siz; ++k) dp[i][k] = 0;
            }
        }
        cout << fixed << setprecision(16) << ans << "\n";
    }
    return 0;
}