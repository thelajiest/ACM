#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5 + 10;

int root[N], idx, n;
LL ans[N];
struct PST {
    int lson, rson;
    int num;
    LL sum;
} tr[N << 5];

struct node {
    int a, b;
    bool operator<(node &tem) { return b < tem.b; }
} res[N];

vector<int> diz;

void build(int &x, int l, int r) {
    x = ++idx;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(tr[x].lson, l, mid);
    build(tr[x].rson, mid + 1, r);
}

int find(int x) {
    return lower_bound(diz.begin(), diz.end(), x) - diz.begin() + 1;
}

void insert(int &x, int y, int l, int r, int c) {
    x = ++idx;
    tr[x] = tr[y];
    tr[x].num++;
    tr[x].sum += diz[c - 1];
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (c <= mid)
        insert(tr[x].lson, tr[y].lson, 1, mid, c);
    else
        insert(tr[x].rson, tr[y].rson, mid + 1, r, c);
}

LL query(int x, int l, int r, int k) {
    if (l == r) return 1ll * diz[l - 1] * k;
    int mid = (l + r) >> 1;
    int cur = tr[tr[x].lson].num;
    if (cur <= k) {
        return tr[tr[x].lson].sum + query(tr[x].rson, mid + 1, r, k - cur);
    } else
        return query(tr[x].lson, l, mid, k);
}

void solve(int kl, int kr, int xl, int xr) {
    if (kl > kr) return;
    int kmid = (kl + kr) >> 1;
    LL cur = 1e18;
    int xmid = 0;
    for (int i = max(xl, kmid); i <= xr; i++) {
        if (1ll * res[i].b + res[i].a +
                query(root[i - 1], 1, diz.size(), kmid - 1) <
            cur) {
            cur = 1ll * res[i].b + res[i].a +
                  query(root[i - 1], 1, diz.size(), kmid - 1);
            xmid = i;
        }
    }
    ans[kmid] = cur;
    solve(kl, kmid - 1, xl, xmid);
    solve(kmid + 1, kr, xmid, xr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> res[i].a >> res[i].b;
        diz.push_back(res[i].a);
    }
    sort(res + 1, res + 1 + n);
    sort(diz.begin(), diz.end());
    diz.erase(unique(diz.begin(), diz.end()), diz.end());
    build(root[0], 1, diz.size());
    for (int i = 1; i <= n; i++) {
        insert(root[i], root[i - 1], 1, diz.size(), find(res[i].a));
    }
    solve(1, n, 1, n);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
