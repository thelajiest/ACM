#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 2e2 + 7;
int dp[MAX_N][MAX_N][MAX_N];
string a;
int T, n, m;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        cin >> a;
        if (m & 1) {
            cout << "0\n";
            continue;
        }
        dp[0][0][0] = 1;
        for (int i = 0; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int k = 0; k <= m / 2; ++k) {
                    if (k) {
                        if (i && a[i - 1] == '(') {
                            dp[i][j][k] =
                                (dp[i - 1][j - 1][k - 1] + dp[i][j][k]) % MOD;
                        } else {
                            dp[i][j][k] =
                                (dp[i][j - 1][k - 1] + dp[i][j][k]) % MOD;
                        }
                    }
                    if (k < m / 2) {
                        if (i && a[i - 1] == ')') {
                            dp[i][j][k] =
                                (dp[i - 1][j - 1][k + 1] + dp[i][j][k]) % MOD;
                        } else {
                            dp[i][j][k] =
                                (dp[i][j - 1][k + 1] + dp[i][j][k]) % MOD;
                        }
                    }
                }
            }
        }
        cout << dp[n][m][0] << "\n";
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int k = 0; k <= m / 2; ++k) {
                    dp[i][j][k] = 0;
                }
            }
        }
    }
    return 0;
}