#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> t(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }

    vector<int> dp(n + 1);
    function<void(int, int)> dfs = [&](int u, int fa) {
        for (auto v : t[u]) {
            if (v == fa) continue;
            dfs(v, u);
            dp[u] += dp[v];
        }
        if (dp[u] > 0)
            dp[u]--;
        else
            dp[u]++;
    };
    dfs(1, 0);

    if (dp[1] == 0)
        cout << "Bob";
    else
        cout << "Alice";

    return 0;
}