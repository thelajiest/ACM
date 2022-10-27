/*我没有所謂*/
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 7;
int a[MAX_N], dp[MAX_N];
int T, n;

int dfs(int x) {
    if (dp[x] != -1) return dp[x];
    dp[x] = 0;
    if (x && a[x - 1] < a[x]) {
        dp[x] = max(dp[x], dfs(x - 1) + 1);
    }
    if (x < n - 1 && a[x + 1] < a[x]) {
        dp[x] = max(dp[x], dfs(x + 1) + 1);
    }
    return dp[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            dp[i] = -1;
        }
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += a[i] - dfs(i);
        }
        cout << "Case " << cas << ": ";
        if (sum & 1) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
    return 0;
}