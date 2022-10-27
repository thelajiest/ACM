#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 1E6 + 100;
const int INF = MAX_N;
using pii = pair<int, int>;

// 线段树维护区间最小值以及位置
class SegmentTree {
   private:
    int n;
    pii a[MAX_N << 2];

    void init(int n, int l, int r) {
        a[n].first = INF, a[n].second = l;
        if (l == r) return;
        int mid = (l + r) >> 1;
        init(n << 1, l, mid);
        init(n << 1 | 1, mid + 1, r);
    }

    void modify(int n, int l, int r, int p, int x) {
        if (l == r) {
            a[n].first = x;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid)
            modify(n << 1, l, mid, p, x);
        else
            modify(n << 1 | 1, mid + 1, r, p, x);
        a[n] = min(a[n << 1], a[n << 1 | 1]);
    }

    pii query(int n, int l, int r, int ll, int rr) {
        if (ll <= l && r <= rr) {
            return a[n];
        }
        int mid = (l + r) >> 1;
        pii al = pii(INF, 0), ar = pii(INF, 0);
        if (ll <= mid) al = query(n << 1, l, mid, ll, rr);
        if (mid < rr) ar = query(n << 1 | 1, mid + 1, r, ll, rr);
        return min(al, ar);
    }

   public:
    void init(int _n) {
        n = _n;
        init(1, 1, n);
    }

    void modify(int p, int x) { modify(1, 1, n, p, x); }

    pii query(int l, int r) { return query(1, 1, n, l, r); }
} tr;

int T;
int n, k;
int a[MAX_N], b[MAX_N];
// 需要记录的是对于每一种位置的下一个目标位置是多少
int tar[MAX_N][2];  // 0为靠左，1为靠右

pii get_tar(int l, int r) {
    if (l > n) l -= n;
    if (r < 1) r += n;
    if (l <= r)
        return tr.query(l, r);
    else
        return min(tr.query(1, r), tr.query(l, n));
}

map<pii, int> dis;
set<pii> vis;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) cin >> a[i], b[a[i]] = i;

        if (n == k) {
            cout << 0 << '\n';
            continue;
        }

        tr.init(n);

        for (int i = n; i >= 1; --i) {
            pii tmp = get_tar(i + 1, i - k);  //靠左
            tar[i][0] = INF == tmp.first ? 0 : tmp.second;
            tmp = get_tar(i + k, i - 1);  // 靠右
            tar[i][1] = INF == tmp.first ? 0 : tmp.second;

            tr.modify(b[i], i);
        }

        vis.clear();
        dis.clear();
        int ans = INF * INF;
        int cur = 1;
        while (1 <= b[cur] && b[cur] <= k) cur += 1;
        // <下个目标，当前位置>
        queue<pii> que;
        que.emplace(cur, 1);
        dis[pii(cur, 1)] = 0;
        while (!que.empty()) {
            pii it = que.front();
            que.pop();
            if (vis.find(it) != vis.end()) continue;
            vis.insert(it);
            int v = it.first, pos = it.second, w = dis[it];
            // cerr << v << ' ' << pos << ' ' << w << endl;

            // 使得左端到达v
            int w1 = min(abs(pos - b[v]), n - abs(pos - b[v]));
            // cerr << pos << ' ' << b[v] << ' ' << w1 << endl;
            if (tar[v][0]) {
                if (dis.find(pii(tar[v][0], b[v])) != dis.end()) {
                    dis[pii(tar[v][0], b[v])] =
                        min(dis[pii(tar[v][0], b[v])], w + w1);
                } else {
                    dis[pii(tar[v][0], b[v])] = w + w1;
                }
                que.emplace(tar[v][0], b[v]);
            } else {
                ans = min(ans, w + w1);
            }
            // 使得右端到达v
            pos += k - 1;
            if (pos > n) pos -= n;
            int w2 = min(abs(pos - b[v]), n - abs(pos - b[v]));
            // cerr << pos << ' ' << b[v] << ' ' << w2 << endl;
            if (tar[v][1]) {
                int tmp = b[v] - k + 1;
                if (tmp < 1) tmp += n;
                if (dis.find(pii(tar[v][1], tmp)) != dis.end()) {
                    dis[pii(tar[v][1], tmp)] =
                        min(dis[pii(tar[v][1], tmp)], w + w2);
                } else {
                    dis[pii(tar[v][1], tmp)] = w + w2;
                }
                que.emplace(tar[v][1], tmp);
            } else {
                ans = min(ans, w + w2);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}