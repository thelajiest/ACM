#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 2E5 + 100;
const int MOD = 1E9 + 7;

int bin(int x, int n) {
    int ret = 1;
    for (; n; x = x * x % MOD, n >>= 1) {
        if (n & 1) {
            ret = ret * x % MOD;
        }
    }
    return ret;
}

int inv(int x) { return bin(x, MOD - 2); }

int T, n, ans;
vector<int> G[MAX_N];
int sg[MAX_N];

void dfs1(int u, int fat) {
    for (int v : G[u]) {
        if (v == fat) continue;
        dfs1(v, u);
        sg[u] ^= sg[v] + 1;
    }
}

void dfs2(int u, int fat) {
    if (sg[u]) ans += 1;
    for (int v : G[u]) {
        if (v == fat) continue;

        sg[u] ^= sg[v] + 1;
        sg[v] ^= sg[u] + 1;
        dfs2(v, u);
        sg[v] ^= sg[u] + 1;
        sg[u] ^= sg[v] + 1;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            G[i].clear();
            sg[i] = 0;
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        ans = 0;
        dfs1(1, 0);
        dfs2(1, 0);
        cout << ans * inv(n) % MOD << '\n';
    }

    return 0;
}