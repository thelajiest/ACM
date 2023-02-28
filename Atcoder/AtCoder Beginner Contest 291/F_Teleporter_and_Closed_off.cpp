#include <bits/stdc++.h>
#define pLL pair<long long, long long>
#define LL long long

using namespace std;

char buf[1 << 20], *p1 = buf, *p2 = buf;
inline LL read() {
    char c = getchar();
    LL x = 0, f = 1;
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

struct Edge {
    int from, to;
    LL w;
    int nxt;
} e[2000005], e2[2000005];
int head[100005], head2[100005], cut = 0, cut2 = 0;

void Addedge(int x, int y, LL w) {
    e[++cut] = {x, y, w, head[x]};
    head[x] = cut;
}

void Addedgef(int x, int y, LL w) {
    e2[++cut2] = {x, y, w, head2[x]};
    head2[x] = cut2;
}

priority_queue<pLL> q;
int vis[100005];
void DP(int s, LL d[], int head[], Edge e[]) {
    q.push({d[s] = 0, s});
    while (!q.empty()) {
        pLL now = q.top();
        q.pop();
        int u = now.second;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int to = e[i].to;
            LL w = e[i].w;
            if (d[to] > d[u] + w) {
                d[to] = d[u] + w;
                q.push({-d[to], to});
            }
        }
    }
}

int d[100005];
int id[100005], fid[100005], pos = 0;
queue<int> qq;
void Top(int s, int n) {
    for (int i = 1; i <= n; i++) {
        if (d[i] == 0) {
            qq.push(i);
        }
    }
    while (!qq.empty()) {
        int now = qq.front();
        qq.pop();
        id[now] = ++pos;
        fid[pos] = now;
        for (int i = head[now]; i; i = e[i].nxt) {
            d[e[i].to]--;
            if (!d[e[i].to]) {
                qq.push(e[i].to);
            }
        }
    }
}

LL ans[100005];
LL d1[100005], d2[100005];
LL inf;
struct Tree {
    LL mi[100005 * 4];
    void init() {
        memset(mi, 0x3f, sizeof(mi));
        inf = mi[0];
    }
    void up_data(int rt, int l, int r, int L, int R, LL w) {
        if (l == L && r == R) {
            mi[rt] = min(mi[rt], w);
            return;
        }
        int mid = l + r >> 1;
        if (R <= mid)
            up_data(rt << 1, l, mid, L, R, w);
        else if (L > mid)
            up_data(rt << 1 | 1, mid + 1, r, L, R, w);
        else
            up_data(rt << 1, l, mid, L, mid, w),
                up_data(rt << 1 | 1, mid + 1, r, mid + 1, R, w);
    }
    void qurey(int rt, int l, int r, LL w) {
        if (l == r) {
            if (d1[fid[l]] == inf || d2[fid[l]] == inf)
                ans[fid[l]] = w;
            else
                ans[fid[l]] = mi[rt];
            return;
        } else {
            int mid = l + r >> 1;
            mi[rt << 1] = min(mi[rt << 1], mi[rt]);
            mi[rt << 1 | 1] = min(mi[rt << 1 | 1], mi[rt]);
            qurey(rt << 1, l, mid, w);
            qurey(rt << 1 | 1, mid + 1, r, w);
        }
    }
} T;

char ss[100];
int main() {
    int n = read(), m = read();
    int x, y;
    int s = 1, t = n;
    int cntm = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> ss;
        for (int j = 0; j < m; j++) {
            if (ss[j] == '1') {
                d[i + j + 1]++;
                cntm++;
                Addedge(i, i + j + 1, 1);
                Addedgef(i + j + 1, i, 1);
            }
        }
    }
    memset(d1, 0x3f, sizeof(d1));
    memset(vis, 0, sizeof(vis));
    DP(s, d1, head, e);
    memset(d2, 0x3f, sizeof(d2));
    memset(vis, 0, sizeof(vis));
    DP(t, d2, head2, e2);
    Top(s, n);
    T.init();
    for (int i = 1; i <= cntm; i++) {
        int x = e[i].from, y = e[i].to;
        if (id[x] != id[y] - 1 && d1[x] != inf && d2[y] != inf) {
            T.up_data(1, 1, n, id[x] + 1, id[y] - 1, d1[x] + d2[y] + e[i].w);
        }
    }
    T.qurey(1, 1, n, d1[t]);
    for (int x = 2; x <= n - 1; x++) {
        printf("%lld ", (ans[x] == inf) ? -1 : ans[x]);
    }

    return 0;
}
