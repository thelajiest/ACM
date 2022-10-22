#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> mp(n + 1);

    for (int i = 1; i <= n; i++) {
        string x;
        cin >> x;
        x = " " + x;
        mp[i] = {x.begin(), x.end()};
    }

    deque<pair<int, int>> Q;

    static vector<pair<int, int>> d = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    auto check = [&](int x, int y) {
        if (x < 1 || x > n || y < 1 || y > m) return false;
        if (x >= 2 && mp[x - 1][y] == '#') return false;
        if (x <= n - 1 && mp[x + 1][y] == '#') return false;
        if (y >= 2 && mp[x][y - 1] == '#') return false;
        if (y <= m - 1 && mp[x][y + 1] == '#') return false;
        return true;
    };
    vector<vector<int>> dis(n + 1, vector<int>(m + 1, n * m + 1));
    vector<vector<int>> vis(n + 1, vector<int>(m + 1, 0));
    vector<vector<pair<int, int>>> last(n + 1, vector<pair<int, int>>(m + 1));
    for (int i = 1; i <= n; i++) {
        if (!check(i, 1)) continue;
        if (mp[i][1] == '#') {
            Q.emplace_front(i, 1);
            dis[i][1] = 0;
        } else {
            Q.emplace_back(i, 1);
            dis[i][1] = 1;
        }
        vis[i][1] = 1;
        last[i][1] = {-1, -1};
    }
    while (!Q.empty()) {
        auto [x, y] = Q.front();
        Q.pop_front();
        for (auto [dx, dy] : d) {
            if (!check(x + dx, y + dy) || vis[x + dx][y + dy]) continue;
            if (mp[x + dx][y + dy] == '#') {
                dis[x + dx][y + dy] = dis[x][y];
                Q.emplace_front(x + dx, y + dy);
            } else {
                dis[x + dx][y + dy] = dis[x][y] + 1;
                Q.emplace_back(x + dx, y + dy);
            }
            last[x + dx][y + dy] = {x, y};
            vis[x + dx][y + dy] = 1;
        }
    }

    int BestEnd = 1;
    for (int i = 1; i <= n; i++) {
        if (dis[i][m] < dis[BestEnd][m]) BestEnd = i;
    }

    if (dis[BestEnd][m] == n * m + 1) {
        cout << "No\n";
        return;
    }

    int nowx = BestEnd, nowy = m;
    while (pair<int, int>(nowx, nowy) != pair<int, int>{-1, -1}) {
        mp[nowx][nowy] = '#';
        auto [x, y] = last[nowx][nowy];
        swap(x, nowx), swap(y, nowy);
    }
    cout << "Yes\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cout << mp[i][j];
        cout << '\n';
    }

    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}