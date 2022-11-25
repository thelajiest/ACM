#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;

    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        deg[y]++;
    }

    priority_queue<int, vector<int>, greater<int>> Q;

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) Q.push(i);
    }

    vector<int> ans;

    while (!Q.empty()) {
        auto u = Q.top();
        Q.pop();
        ans.push_back(u);
        for (auto v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                Q.push(v);
            }
        }
    }

    if (ans.size() != n) {
        cout << "-1\n";
    } else {
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    return 0;
}