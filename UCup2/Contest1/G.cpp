#include <bits/stdc++.h>
using namespace std;

#define int long long
using pii = pair<int, int>;
const int MAX_N = 1E5 + 100;

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

class SegmentTree {
   private:
    struct Node {
        int a;  // 区间和
        Node *l, *r;
    };

    int n, m, t;
    Node nd[MAX_N * 100];
    Node* rt[MAX_N];

   public:
    void init(int _n) {
        for (int i = 0; i < m; ++i) nd[i] = Node();
        for (int i = 0; i < t; ++i) rt[i] = nullptr;
        n = _n;
        m = t = 1;
    }

    void modify(int p) {
        rt[t] = modify(rt[t - 1], 1, n, p);
        t += 1;
    }

    int query(int l, int r, int p, int q) {
        // 区间 [l, r] 中 [p, q] 的数量
        if (l > r) return 0;
        if (p > q) return 0;
        return query(rt[r], 1, n, p, q) - query(rt[l - 1], 1, n, p, q);
    }

   private:
    Node* modify(Node* it, int l, int r, int p) {
        // 求单点
        Node* nw = nd + (m++);
        nw->a = (it ? it->a : 0) + 1;
        if (l != r) {
            nw->l = it ? it->l : nullptr;
            nw->r = it ? it->r : nullptr;
            int mid = (l + r) >> 1;
            if (p <= mid) {
                nw->l = modify(it ? it->l : nullptr, l, mid, p);
            } else {
                nw->r = modify(it ? it->r : nullptr, mid + 1, r, p);
            }
        }
        return nw;
    }

    int query(Node* it, int l, int r, int ll, int rr) {
        // 查前缀和
        // cerr << "err " << l << ' ' << r << endl;
        if (!it) return 0;
        if (ll <= l && r <= rr) {
            return it->a;
        }
        int mid = (l + r) >> 1, ret = 0;
        if (ll <= mid && it->l) {
            ret += query(it->l, l, mid, ll, rr);
        }
        if (mid < rr && it->r) {
            ret += query(it->r, mid + 1, r, ll, rr);
        }
        return ret;
    }
};

int T;
int n, m;
int x[MAX_N];
SegmentTree tr;

signed main() {
    T = read();
    while (T--) {
        n = read();
        tr.init(n);
        map<pii, int> mp;
        priority_queue<pair<int, pii>> que;

        int z = 0;
        for (int i = 1; i <= n; ++i) {
            x[i] = read();
            tr.modify(x[i]);
            // int tmp = tr.query(1, i, x[i] + 1, n);
            // cerr << "tmp " << tmp << endl;
            z += tr.query(1, i, x[i] + 1, n);  // 查询大于 x[i]
            // cerr << "err " << z << endl;
        }
        que.emplace(pair<int, pii>(z, pii(1, n)));
        mp[pii(n, 1)] = z;

        for (int i = 1; i <= n; ++i) {
            // printf("%lld ", z);
            cout << z << ' ';
            int p = z ^ read();

            auto it = *mp.lower_bound(pii(p, -1));
            int l = it.first.second, r = it.first.first, w = it.second;
            // cerr << "err " << l << ',' << r << ':' << w << endl;
            mp.erase(it.first);

            int w1 = 0, w2 = 0;
            pii d1 = pii(p - 1, l), d2 = pii(r, p + 1);
            w -= tr.query(l, p - 1, x[p] + 1, n);  // 减去靠前区间中大于 x[p]
            w -= tr.query(p + 1, r, 1, x[p] - 1);  // 减去靠后区间中小于 x[p]
            if (p - 1 - l < r - p - 1) {
                // 靠前区间较短，暴力之
                for (int i = l; i <= p - 1; ++i) {
                    w1 += tr.query(l, i, x[i] + 1, n);
                    w -= tr.query(p + 1, r, 1, x[i] - 1);
                }
                w2 = w - w1;
            } else {
                for (int i = p + 1; i <= r; ++i) {
                    w2 += tr.query(p + 1, i, x[i] + 1, n);
                    w -= tr.query(l, p - 1, x[i] + 1, n);
                }
                w1 = w - w2;
            }
            if (l <= p - 1) {
                mp[d1] = w1;
                que.emplace(make_pair(w1, d1));
            }
            if (p + 1 <= r) {
                mp[d2] = w2;
                que.emplace(make_pair(w2, d2));
            }

            while (!que.empty()) {
                int w = que.top().first;
                pii it = que.top().second;
                if (mp.find(it) == mp.end())
                    que.pop();
                else {
                    z = w;
                    break;
                }
            }
        }
        cout << '\n';
    }

    return 0;
}
/*
5 5
5 1 2 4 3
1 1 1
1 4 1
2 4 1
3 4 1
1 5 1

*/