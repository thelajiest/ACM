#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    cin >> n >> m;

    vector<vector<pair<int, i64>>> adj(n + 1);

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        i64 w;
        cin >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int q;
    cin >> q;

    vector<pair<int, int>> limit(q);
    for (auto& [u, v] : limit) cin >> u >> v;

    for (int i = 0; i < (1 << q); i++) {
    }
    return 0;
}