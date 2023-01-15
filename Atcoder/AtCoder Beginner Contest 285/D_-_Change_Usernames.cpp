#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::map<std::string, int> mp;
    int cur = 0;

    std::vector<std::vector<int>> adj(2 * n + 2);

    std::vector<std::pair<std::string, std::string>> E;
    for (int i = 0; i < n; i++) {
        std::string s, t;
        std::cin >> s >> t;
        E.emplace_back(s, t);
        if (!mp[s]) mp[s] = ++cur;
        if (!mp[t]) mp[t] = ++cur;
    }

    std::vector<int> deg(cur + 1);
    for (auto [u, v] : E) {
        adj[mp[u]].push_back(mp[v]);
        deg[mp[v]]++;
    }

    std::queue<int> Q;
    for (int i = 1; i <= cur; i++) {
        if (deg[i] == 0) Q.push(i);
    }

    std::vector<int> ans;
    while (!Q.empty()) {
        auto u = Q.front();
        ans.push_back(u);
        Q.pop();
        for (auto v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                Q.push(v);
            }
        }
    }

    if (ans.size() == cur)
        std::cout << "Yes";
    else
        std::cout << "No";
    return 0;
}