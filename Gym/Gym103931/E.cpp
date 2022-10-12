#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 7;
const int MAX_M = 1e2 + 7;
char s[MAX_N], f[MAX_M];
int dp[MAX_N][MAX_M], lst[MAX_M];
int T, n, m;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> s >> f;
        n = strlen(s), m = strlen(f);
        for (int i = 0; i < m; ++i) lst[i] = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dp[i][j] = -1;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = m - 1; j >= 0; --j) {
                if (s[i] != f[j]) continue;
                if (!j) {
                    dp[i][j] = max(dp[i][j], i);
                } else {
                    if (lst[j - 1] != -1) {
                        dp[i][j] = max(dp[i][j], dp[lst[j - 1]][j - 1]);
                    }
                }
                if (dp[i][j] >= 0) lst[j] = i;
                // cout << i << " " << j << ": " << dp[i][j] << endl;
            }
        }
        int ans = n, l = 0, r = n - 1;
        for (int i = 0; i < n; ++i) {
            if (dp[i][m - 1] >= 0) {
                if (ans > (i - dp[i][m - 1] + 1)) {
                    ans = i - dp[i][m - 1] + 1;
                    l = dp[i][m - 1];
                    r = i;
                }
            }
        }
        for (int i = l; i <= r; ++i) cout << s[i];
        cout << "\n";
    }
    return 0;
}
