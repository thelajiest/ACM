#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAX_N = 2e3 + 7;
int L[MAX_N << 1], R[MAX_N << 1];
bool vis[MAX_N << 1];
int dp[MAX_N];
int n, l, r;

int dfs(int i) {
    if (dp[i] != -1) return dp[i];
    set<int> mex;
    for (int j = 0; j <= i - l; ++j) {
        mex.insert(dfs(j) ^ dfs(i - j - l));
    }
    int res = 0;
    while (true) {
        if (mex.count(res)) {
            ++res;
            continue;
        }
        return res;
    }
}

void solve() {
    cout << "First" << endl;
    int x, y;
    int a, b;
    if ((n - l) & 1) {
        x = (n - l - 1) / 2 + 1;
        y = x + l;
    } else {
        x = (n - l) / 2 + 1;
        y = x + l - 1;
    }
    cout << x << " " << y << endl;
    while (true) {
        cin >> a >> b;
        if (a == 0 && b == 0) return;
        if (a == -1 && b == -1) return;
        x = n + 1 - b;
        y = n + 1 - a;
        cout << x << " " << y << endl;
    }
}

pii pat(int u, int e) {
    int l = L[u], r = R[u], n = R[u] - L[u] + 1;
    int x = 0, y = 0;
    for (int i = 0; i <= n - l; ++i) {
        if ((dp[i] ^ dp[n - i - l]) == e) {
            x = l + i;
            y = x + l - 1;
            break;
        }
    }
    vis[u << 1] = vis[u << 1 | 1] = true;
    L[u << 1] = l, R[u << 1] = x - 1;
    L[u << 1 | 1] = y + 1, R[u << 1 | 1] = r;
    return make_pair(x, y);
}

void pat(int u, int a, int b) {
    vis[u << 1] = vis[u << 1 | 1] = true;
    L[u << 1] = L[u], R[u << 1] = a - 1;
    L[u << 1 | 1] = b + 1, R[u << 1 | 1] = R[u];
}

int find(int u, int a, int b) {
    if (!vis[u]) return -1;
    int res = u;
    if (b <= R[u << 1]) {
        int nxt = find(u << 1, a, b);
        if (nxt != -1) res = (u << 1);
    } else if (a >= L[u << 1 | 1]) {
        int nxt = find(u << 1 | 1, a, b);
        if (nxt != -1) res = (u << 1 | 1);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> l >> r;
    // r > l
    if (r > l) {
        solve();
    } else {
        for (int i = 0; i <= n; ++i) dp[i] = -1;
        for (int i = 1; i <= n; ++i) {
            if (dp[i] == -1) dfs(i);
        }
        int x, y;
        int a, b;
        vis[1] = true;
        L[1] = 1, R[1] = n;
        if (dp[n]) {
            cout << "First" << endl;
            pii p = pat(1, dp[n]);
            x = p.first, y = p.second;
            cout << x << " " << y << endl;
        } else {
            cout << "Second" << endl;
            cin >> a >> b;
            if (a == 0 && b == 0) return 0;
            if (a == -1 && b == -1) return 0;
            pat(1, a, b);
            pii p = pat(2, dp[R[2] - L[2] + 1]);
            x = p.first, y = p.second;
            cout << x << " " << y << endl;
        }
        while (true) {
            cin >> a >> b;
            if (a == 0 && b == 0) break;
            if (a == -1 && b == -1) break;
            int u = find(1, a, b);
            int e = dp[a - L[u]] ^ dp[R[u] - b];
            pii p = pat(u ^ 1, e);
            x = p.first, y = p.second;
            cout << x << " " << y << endl;
        }
    }
    return 0;
}