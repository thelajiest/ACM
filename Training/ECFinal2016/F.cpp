#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <class T, class Cmp = less<T>>
struct RMQ {
    const int n;
    const Cmp cmp;
    vector<vector<T>> a;
    RMQ(const vector<T> &init) : n(init.size()), cmp(Cmp()) {
        int lg = __lg(n);
        a.assign(lg + 1, vector<T>(n));
        for (int j = 0; j <= lg; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                a[j][i] = (j == 0 ? init[i]
                                  : min(a[j - 1][i],
                                        a[j - 1][i + (1 << (j - 1))], cmp));
            }
        }
    }
    T rangeMin(int l, int r) {
        int k = __lg(r - l);
        return min(a[k][l], a[k][r - (1 << k)], cmp);
    }
};

template <class T>
struct SuffixArrayFast {
    int n;
    vector<int> sa, rk, lc;
    RMQ<int> *rmq;

    vector<int> sa_is(const vector<int> &s) const {
        const int n = (int)s.size();
        vector<int> ret(n);

        vector<int> is_s(n), is_lms(n);
        int m = 0;
        for (int i = n - 2; i >= 0; i--) {
            is_s[i] = (s[i] > s[i + 1]) or (s[i] == s[i + 1] and is_s[i + 1]);
            m += (is_lms[i + 1] = is_s[i] and not is_s[i + 1]);
        }

        auto induced_sort = [&](const vector<int> &lms) {
            int upper = *max_element(s.begin(), s.end());
            vector<int> l(upper + 2), r(upper + 2);
            for (auto &&v : s) {
                ++l[v + 1];
                ++r[v];
            }
            partial_sum(l.begin(), l.end(), l.begin());
            partial_sum(r.begin(), r.end(), r.begin());
            fill(ret.begin(), ret.end(), -1);
            for (int i = (int)lms.size() - 1; i >= 0; i--) {
                ret[--r[s[lms[i]]]] = lms[i];
            }
            for (auto &&v : ret) {
                if (v >= 1 and is_s[v - 1]) ret[l[s[v - 1]]++] = v - 1;
            }
            fill(r.begin(), r.end(), 0);
            for (auto &&v : s) ++r[v];
            partial_sum(r.begin(), r.end(), r.begin());
            for (int k = (int)ret.size() - 1, i = ret[k]; k >= 1;
                 i = ret[--k]) {
                if (i >= 1 and not is_s[i - 1]) {
                    ret[--r[s[i - 1]]] = i - 1;
                }
            }
        };

        vector<int> lms;
        lms.reserve(m);
        for (int i = 1; i < n; i++) {
            if (is_lms[i]) lms.push_back(i);
        }

        induced_sort(lms);

        vector<int> new_lms;
        new_lms.reserve(m);
        for (int i = 0; i < n; i++) {
            if (not is_s[ret[i]] and ret[i] > 0 and is_s[ret[i] - 1]) {
                new_lms.push_back(ret[i]);
            }
        }

        auto is_same = [&](int a, int b) {
            if (s[a++] != s[b++]) return false;
            for (;; ++a, ++b) {
                if (s[a] != s[b]) return false;
                if (is_lms[a] or is_lms[b]) return is_lms[a] and is_lms[b];
            }
        };

        int rank = 0;
        ret[n - 1] = 0;
        for (int i = 1; i < m; i++) {
            if (not is_same(new_lms[i - 1], new_lms[i])) ++rank;
            ret[new_lms[i]] = rank;
        }

        if (rank + 1 < m) {
            vector<int> new_s(m);
            for (int i = 0; i < m; i++) {
                new_s[i] = ret[lms[i]];
            }
            auto lms_sa = sa_is(new_s);
            for (int i = 0; i < m; i++) {
                new_lms[i] = lms[lms_sa[i]];
            }
        }

        induced_sort(new_lms);

        return ret;
    }

    SuffixArrayFast(const T &vs, bool compress = false) : rmq(nullptr) {
        vector<int> new_vs(vs.size() + 1);
        if (compress) {
            T xs = vs;
            sort(xs.begin(), xs.end());
            xs.erase(unique(xs.begin(), xs.end()), xs.end());
            for (int i = 0; i < (int)vs.size(); i++) {
                new_vs[i] = std::lower_bound(xs.begin(), xs.end(), vs[i]) -
                            xs.begin() + 1;
            }
        } else {
            auto d = *min_element(vs.begin(), vs.end());
            for (int i = 0; i < (int)vs.size(); i++) {
                new_vs[i] = vs[i] - d + 1;
            }
        }
        auto res = sa_is(new_vs);
        sa.assign(begin(res) + 1, end(res));
        n = sa.size();
        rk.resize(n);
        lc.resize(n - 1);
        for (int i = 0; i < n; i++) {
            rk[sa[i]] = i;
        }
        for (int i = 0, j = 0; i < n; ++i) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n &&
                                 vs[i + j] == vs[sa[rk[i] - 1] + j];)
                    ++j;
                lc[rk[i] - 1] = j;
            }
        }
        if (n > 1) {
            rmq = new RMQ(lc);
        }
    }
    ~SuffixArrayFast() {
        if (rmq) {
            delete rmq;
        }
    }
    int lcp(int x, int y) {
        if (x == n || y == n) {
            return 0;
        }
        if (x == y) {
            return n - x;
        }
        x = rk[x];
        y = rk[y];
        if (x > y) {
            swap(x, y);
        }
        return rmq->rangeMin(x, y);
    }
};

void solve() {
    int n;
    cin >> n;

    string comb;
    int siz = 0;
    for (int i = 0; i < n; i++) {
        string res;
        cin >> res;
        if (i == 0) {
            siz = res.size();
        }
        comb += res;
        if (i != n - 1) comb += "#";
    }
    SuffixArrayFast<string> Sa(comb);

    constexpr int INF = 0x3f3f3f3f;

    tuple<int, int, int> ans = {-INF, INF, INF};

    vector<int> pre(siz), suf(siz);
    int now = -1;
    for (int i = 0; i < Sa.n; i++) {
        if (Sa.sa[i] >= siz)
            now = Sa.sa[i];
        else
            pre[Sa.sa[i]] = now;
    }
    now = -1;
    for (int i = Sa.n - 1; i >= 0; i--) {
        if (Sa.sa[i] >= siz)
            now = Sa.sa[i];
        else
            suf[Sa.sa[i]] = now;
    }
    for (int i = 0; i < siz; i++) {
        int rk = Sa.rk[i];
        int lcp = -INF;
        if (pre[i] >= siz) {
            int lcp1 = Sa.lcp(pre[i], i);
            lcp = max(lcp, lcp1);
        }
        if (suf[i] >= siz) {
            int lcp2 = Sa.lcp(i, suf[i]);
            lcp = max(lcp, lcp2);
        }
        if (i + lcp < siz) {
            auto [l, r, ansrk] = ans;
            if (lcp + 1 < r - l + 1 || (lcp + 1 == r - l + 1 && ansrk > rk))
                ans = {i, i + lcp, rk};
        }
    }
    auto [l, r, ansrk] = ans;
    if (l == -INF && r == INF) {
        cout << "Impossible" << '\n';
    } else {
        for (int i = l; i <= r; i++) {
            cout << comb[i];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}