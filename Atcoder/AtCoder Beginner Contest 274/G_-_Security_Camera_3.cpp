#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

using namespace std;
using ll = long long;
using Vi = vector<int>;
using Pii = pair<int, int>;
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define rep(i, b, e) for (int i = (b); i < (e); i++)
#define each(a, x) for (auto& a : (x))
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
struct Matching : Vi {
    vector<Vi> adj;
    Vi rank, low, pos, vis, seen;
    int k{0};

    Matching(int n = 0) : Vi(n, -1), rank(n) {}

    bool add(Vi vec) {
        adj.pb(move(vec));
        low.pb(0);
        pos.pb(0);
        vis.pb(0);
        if (!adj.back().empty()) {
            int i = k;
        nxt:
            seen.clear();
            if (dfs(sz(adj) - 1, ++k - i)) return 1;
            each(v, seen)
                each(e, adj[v]) if (rank[e] < 1e9 && vis[at(e)] < k) goto nxt;
            each(v, seen) {
                low[v] = 1e9;
                each(w, adj[v]) rank[w] = 1e9;
            }
        }
        return 0;
    }

    bool dfs(int v, int g) {
        if (vis[v] < k) vis[v] = k, seen.pb(v);
        while (low[v] < g) {
            int e = adj[v][pos[v]];
            if (at(e) != v && low[v] == rank[e]) {
                rank[e]++;
                if (at(e) == -1 || dfs(at(e), rank[e])) return at(e) = v, 1;
            } else if (++pos[v] == sz(adj[v])) {
                pos[v] = 0;
                low[v]++;
            }
        }
        return 0;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<vector<char>> mp(h);
    for (int i = 0; i < h; i++) {
        string s;
        cin >> s;
        mp[i] = {s.begin(), s.end()};
    }

    auto check = [&](int x, int y) {
        if (x < 0 || x >= h || y < 0 || y >= w) return false;
        return true;
    };

    vector<vector<int>> g(h * w + 1), G(h * w + 1);
    vector<pair<int, int>> d = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<pair<int, int>> node;
    int edge = 0;
    pair<int, int> s = {-1, -1};
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            if (mp[x][y] == '#') continue;
            node.emplace_back(x, y);
            s = {x, y};
            for (auto [dx, dy] : d) {
                if (check(x + dx, y + dy) && mp[x + dx][y + dx] != '#') {
                    g[x * h + y].push_back((x + dx) * h + y + dy);
                    g[(x + dx) * h + y + dy].push_back(x * h + y);
                    edge++;
                }
            }
        }
    }
    if (s == pair<int, int>{-1, -1}) {
        cout << 0;
        return 0;
    }

    vector<int> col(h * w + 1);
    auto dfs = [&](auto self, int u, int c) -> void {
        col[u] = c;
        for (auto v : g[u]) {
            if (!col[v]) self(self, v, -c);
        }
    };
    for (auto [x, y] : node) {
        if (col[x * h + y] == 0) dfs(dfs, x * h + y, 1);
    }
    for (auto [x, y] : node) {
        if (col[x * h + y] == 1) {
            for (auto p : g[x * h + y]) G[x * h + y].push_back(p);
        }
    }

    Matching match(edge);

    int ans = 0;
    each(v, G) { ans += match.add(v); }
    cout << ans << '\n';
    return 0;
}