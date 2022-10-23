#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 7;
const int MAX_A = 1e4 + 7;
int dp[2][MAX_A << 1];
int a[MAX_N];
int n, x, y;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> x >> y;
    int sum = 0;
    for (int i = 0; i < n; ++i) cin >> a[i], sum += a[i];
    int N = 1e4;
    int st = 0;
    dp[0][N + a[0]] = 1;
    for (int i = 2; i < n; i += 2) {
        for (int j = N - sum; j <= N + sum; ++j) {
            dp[st ^ 1][j] = 0;
            if (j - a[i] >= N - sum) {
                dp[st ^ 1][j] |= dp[st][j - a[i]];
            }
            if (j + a[i] <= N + sum) {
                dp[st ^ 1][j] |= dp[st][j + a[i]];
            }
        }
        st ^= 1;
    }
    bool flag = dp[st][N + x];
    for (int i = N - sum; i <= N + sum; ++i) dp[0][i] = dp[1][i] = 0;
    st = 0;
    dp[0][N] = 1;
    for (int i = 1; i < n; i += 2) {
        for (int j = N - sum; j <= N + sum; ++j) {
            dp[st ^ 1][j] = 0;
            if (j - a[i] >= N - sum) {
                dp[st ^ 1][j] |= dp[st][j - a[i]];
            }
            if (j + a[i] <= N + sum) {
                dp[st ^ 1][j] |= dp[st][j + a[i]];
            }
#ifdef sleepy
            cout << j - N << ": " << dp[st ^ 1][j] << endl;
#endif
        }
        st ^= 1;
    }
    if (flag && dp[st][N + y]) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}