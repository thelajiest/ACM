#include <bits/stdc++.h>
#define int long long
// #define sleepy

using namespace std;

typedef pair<int, int> pii;
const int MAX_N = 1e5 + 7;
int mx[MAX_N << 2], which[MAX_N << 2], tag[MAX_N << 2];
int cnt[MAX_N], p[MAX_N];
int n, t;

void pushup(int u) {
    mx[u] = mx[u << 1];
    which[u] = which[u << 1];
    if (mx[u << 1 | 1] > mx[u]) {
        mx[u] = mx[u << 1 | 1];
        which[u] = which[u << 1 | 1];
    }
#ifdef sleepy
    // cerr << u << ": " << mx[u] << ", " << which[u] << "\n";
#endif
}

void pushdown(int u) {
    if (tag[u]) {
        mx[u << 1] = mx[u << 1] + tag[u];
        mx[u << 1 | 1] = mx[u << 1 | 1] + tag[u];
        tag[u << 1] += tag[u];
        tag[u << 1 | 1] += tag[u];
        tag[u] = 0;
    }
}

void build(int u, int l, int r) {
    if (l > r) return;
    if (l == r) {
        mx[u] = p[l];
        which[u] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int l, int r, int x, int y) {
#ifdef sleepy
    cerr << x << " " << u << ": " << l << ", " << r << "<<<" << y << "\n";
#endif
    if (x < l || x > r) return;
    if (l == x && r == x) {
        mx[u] = y;
        return;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    if (x <= mid) modify(u << 1, l, mid, x, y);
    if (x > mid) modify(u << 1 | 1, mid + 1, r, x, y);
    pushup(u);
}

void add(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        mx[u] += 1;
        tag[u] += 1;
        return;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    if (x <= mid) modify(u << 1, l, mid, x, y);
    if (y > mid) modify(u << 1 | 1, mid + 1, r, x, y);
    pushup(u);
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> t;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    build(1, 0, n - 1);
    while (t--) {
#ifdef sleepy
        cerr << mx[1] << ", " << which[1] << " " << p[which[1]] << '\n';
#endif
        ++cnt[which[1]];
        add(1, 0, n - 1, 0, n - 1);
        modify(1, 0, n - 1, which[1], p[which[1]]);
    }
    for (int i = 0; i < n; ++i) cout << cnt[i] << " ";
    cout << "\n";
    return 0;
}