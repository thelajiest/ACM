#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 2E5 + 100;
const int INF = 1E17 + 100;

int T, n;
int a[MAX_N];
int ans[MAX_N][3];
vector<int> G[MAX_N];

void dfs(int u, int fat) {
    int p0 = 0, p1 = INF, p2 = 0;
    for (int v : G[u]) {
        if (v == fat) continue;
        dfs(v, u);
        p2 += min(min(ans[v][2], ans[v][1]),
                  ans[v][0]);  // p2 统计当前点放置时的要求
        p0 += min(ans[v][2], ans[v][1]);
        p1 = min(p1, ans[v][2] - min(ans[v][2], ans[v][1]));
    }
    ans[u][0] = p0;
    ans[u][1] = p0 + p1;
    ans[u][2] = p2 + a[u];
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            G[i].clear();
            ans[i][0] = ans[i][1] = ans[i][2] = INF;
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 0);
        // cerr << "err " << ans[1][1] << ' ' << ans[1][2] << '\n';
        cout << min(ans[1][1], ans[1][2]) << '\n';
    }

    return 0;
}