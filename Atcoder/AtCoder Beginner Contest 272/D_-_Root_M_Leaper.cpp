#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    constexpr int INF = 0x3f3f3f3f;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));

    vector<pair<int, int>> to;

    for (int i = -n; i <= n; i++)
        for (int j = -n; j <= n; j++) {
            if (i * i + j * j == m) {
                to.push_back({i, j});
                if (j != i) to.push_back({j, i});
            }
        }

    queue<pair<int, int>> q;
    q.push({1, 1});
    vector<vector<int>> vis(n + 1, vector<int>(n + 1, 0));
    dp[1][1] = 0;
    vis[1][1] = 1;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (auto [dx, dy] : to) {
            if (1 <= dx + x && dx + x <= n && 1 <= dy + y && dy + y <= n) {
                if (!vis[x + dx][y + dy]) {
                    dp[x + dx][y + dy] = dp[x][y] + 1;
                    vis[x + dx][y + dy] = 1;
                    q.push({x + dx, y + dy});
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << ((dp[i][j] >= INF) ? -1 : dp[i][j]) << " ";
        cout << '\n';
    }

    return 0;
}