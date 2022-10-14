#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int mod = 998244353;
constexpr int N = 3001;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n + 1), B(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) cin >> B[i];

    vector<array<int, N>> dp(n + 1, array<int, N>());

    array<int, N> sum;
    sum.fill(1);
    for (int i = 1; i <= n; i++) {
        int a, b;
        a = A[i], b = B[i];
        for (int j = a; j <= b; j++) {
            dp[i][j] = (dp[i][j] + sum[j]) % mod;
        }
        sum = dp[i];
        for (int i = 1; i < N; i++) sum[i] = (sum[i] + sum[i - 1]) % mod;
    }

    int ans = 0;
    for (int i = 0; i < N; i++) ans = (ans + dp[n][i]) % mod;
    cout << ans << endl;

    return 0;
}