#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr i64 inf = 1e18;
    int n, m;
    cin >> n >> m;

    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<i64>> dp(n + 1, vector<i64>(m + 1, -inf));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = max(dp[i][0], dp[i - 1][0]);
        for (int j = 1; j <= min(i, m); j++) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + j * a[i]);
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}