#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> t(n + 1);
    vector<int> val(n + 1);

    int root;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x == 0) root = i;
        val[i] = x;
    }
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        t[i].push_back(x);
        t[x].push_back(i);
    }

    vector<int> dp(n + 1), siz(n + 1);
    function<void(int, int)> dfs = [&](int u, int fa) {
        siz[u] = 1;
        dp[u] = numeric_limits<int>::max();

        for (auto v : t[u]) {
            if (v == fa) continue;
            dfs(v, u);
            siz[u] += siz[v];
            dp[u] = min({dp[u], dp[v], val[v]});
        }
    };
    dfs(root, 0);
    vector<int> ans(n + 1);

    ans[n] = n;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > val[i])
            ans[val[i]] = n - siz[i];
        else
            ans[val[i]] = 0;
    }
    for (auto v : t[root]) {
        ans[0] = max(ans[0], siz[v]);
    }
    for (int i = 0; i <= n; i++) cout << ans[i] << " \n"[i == n];

    return 0;
}