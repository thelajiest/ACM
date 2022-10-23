#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> t(2 * n + 2);

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        t[x].push_back(2 * i);
        t[x].push_back(2 * i + 1);
    }

    vector<int> dep(2 * n + 2);
    auto dfs = [&](auto self, int u, int fa) -> void {
        dep[u] = dep[fa] + 1;
        for (auto v : t[u]) {
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i <= 2 * n + 1; i++) cout << dep[i] - 1 << '\n';
    return 0;
}