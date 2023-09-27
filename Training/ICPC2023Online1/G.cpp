#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1E6 + 100;
const int MOD = 998244353;

int read() {
    int x = 0;
    char c = getchar();
    while ('0' > c || c > '9') c = getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

int bin(int x, int n) {
    int ret = 1;
    for (; n; n >>= 1, x = 1LL * x * x % MOD) {
        if (n & 1) ret = 1LL * ret * x % MOD;
    }
    return ret;
}

int inv[MAX_N];

int n;
int a[MAX_N], b[MAX_N];
int w[MAX_N];
vector<int> G[MAX_N];
int fat[MAX_N];

int getfat(int u) {
    if (u == fat[u])
        return u;
    else
        return fat[u] = getfat(fat[u]);
}

void merge(int u, int v) {
    u = getfat(u), v = getfat(v);
    if (G[u].size() > G[v].size()) swap(u, v);
    for (int it : G[u]) G[v].push_back(std::move(it));
    std::move(G[u].begin(), G[u].end(), std::back_inserter(G[v]));
    w[v] += w[u];
    fat[u] = v;
}

bool connect(int u, int v) { return getfat(u) == getfat(v); }

signed main() {
    n = read();
    for (int i = 1; i < n; ++i) a[i] = read(), b[i] = read();
    for (int i = 1; i < n; ++i) {
        int u = read(), v = read();
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        fat[i] = i;
        w[i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        inv[i] = bin(i, MOD - 2);
    }
    // init

    int ans = 1;
    for (int i = 1; i < n; ++i) {
        int u = getfat(a[i]), v = getfat(b[i]);

        ans = 1LL * ans * inv[w[u]] % MOD;
        ans = 1LL * ans * inv[w[v]] % MOD;

        if (G[u].size() > G[v].size()) swap(u, v);
        bool ok = false;
        for (int it : G[u]) {
            if (v == getfat(it)) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            ans = 0;
            break;
        }
        merge(u, v);
    }

    printf("%d", ans);
}