#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mp(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        mp[i] = {s.begin(), s.end()};
    }
    int Start;
    auto id = [&](int x, int y) -> int { return m * x + y; };
    vector<vector<int>> g(n * m + 1);
    vector<pair<int, int>> d = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == 'S') Start = id(i, j);
            if (mp[i][j] == '#') continue;
            auto check = [&](int x, int y) -> bool {
                if (x < 0 || x >= n || y < 0 || y >= m) return false;
                if (mp[x][y] == '#') return false;
                return true;
            };
            for (auto [dx, dy] : d) {
                if (check(dx + i, dy + j)) {
                    g[id(i + dx, j + dy)].push_back(id(i, j));
                    g[id(i, j)].push_back(id(i + dx, j + dy));
                }
            }
        }
    }
    vector<int> dfn(n * m + 1), low(n * m + 1), point(n * m + 1);
    vector<vector<int>> BCC(n * m + 1);
    int num = 0;
    int ord = 0;
    stack<int> s;
    auto tarjan = [&](auto self, int u, int fa) -> void {
        dfn[u] = low[u] = ord;
        ord++;
        int child = 0;
        s.push(u);
        for (auto v : g[u]) {
            if (v == fa) continue;
            if (!dfn[v]) {
                child++;
                self(self, v, u);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    point[u] = 1;
                    num++;
                    while (true) {
                        int len = s.top();
                        BCC[num].push_back(len);
                        s.pop();
                        if (len == v) break;
                    }
                    BCC[num].push_back(u);
                }
            } else if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa < 0 && child == 1) point[u] = 0;
    };
    for (int i = 0; i < n * m; i++) {
        if (!dfn[i]) tarjan(tarjan, i, i);
    }
    bool ok = false;
    for (int i = 1; i <= num; i++) {
        for (auto p : BCC[i]) {
            if (p == Start) {
                if (BCC[i].size() >= 4) {
                    ok = true;
                }
            }
        }
    }
    if (ok)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}