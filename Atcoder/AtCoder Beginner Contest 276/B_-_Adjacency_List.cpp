#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
        if (g[i].size() != 0)
            cout << g[i].size() << " ";
        else
            cout << "0\n";
        for (int j = 0; j < g[i].size(); j++)
            cout << g[i][j] << " \n"[j == g[i].size() - 1];
    }

    return 0;
}