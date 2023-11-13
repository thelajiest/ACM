#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// #define sleepy
#define int long long

using namespace std;

using pii = pair<int, int>;

struct Edge {
    int to, w;
};

using Edges = vector<Edge>;

const int MAX_N = 1e5 + 7;
const int INF = 1e18;

int T, n, m, k;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        vector<Edges> g(n, Edges());
        vector<int> e(k), d(n);
        for (int i = 0; i < k; i++) {
            cin >> e[i];
            --e[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> d[i];
        }
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        vector<int> dis(n, INF), vis(n, 0);
        priority_queue<pii> q;
        for (int i = 0; i < k; i++) {
            dis[e[i]] = 0;
            d[e[i]] = 0;
            q.push(make_pair(0, e[i]));
        }
        while (!q.empty()) {
            auto [_dis, u] = q.top();
            q.pop();
            if (vis[u]) continue;
            if (d[u] > 0) {
                --d[u];
                continue;
            }
            vis[u] = true;
            dis[u] = -_dis;
            for (auto &[v, w] : g[u]) {
                if (vis[v]) continue;
                q.push(make_pair(_dis - w, v));
            }
        }
        if (dis[0] < INF) {
            cout << dis[0] << "\n";
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}