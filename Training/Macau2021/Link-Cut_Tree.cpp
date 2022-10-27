#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1E5 + 100;
using pii = pair<int, int>;

int T;
int n, m;
int fat[MAX_N];
vector<pii> G[MAX_N];
vector<int> ans;

int get_fat(int u) {
    if (u == fat[u])
        return u;
    else
        return fat[u] = get_fat(fat[u]);
}

void merge(int u, int v) { fat[get_fat(u)] = get_fat(v); }

bool is_connected(int u, int v) { return get_fat(u) == get_fat(v); }

bool dfs(int u, int fat, int tar) {
    if (u == tar) return true;
    for (pii it : G[u]) {
        int i = it.second;
        int v = it.first;
        if (fat == v) continue;
        if (dfs(v, u, tar)) {
            ans.push_back(i);
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            fat[i] = i;
            G[i].clear();
        }
        ans.clear();

        bool flag = false;
        int uu, vv;
        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            if (flag) continue;
            flag = is_connected(u, v);
            if (flag) {
                ans.push_back(i);
                uu = u, vv = v;
                continue;
            }
            merge(u, v);
            G[u].emplace_back(v, i);
            G[v].emplace_back(u, i);
        }

        if (flag) {
            dfs(uu, 0, vv);
            sort(ans.begin(), ans.end());
            for (int u : ans) {
                cout << u << ' ';
            }
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}