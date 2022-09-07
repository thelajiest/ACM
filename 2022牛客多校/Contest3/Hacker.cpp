#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using pii = pair<int, int>;
using VI = vector<int>;
struct node {
    i64 sum, max_sum, max_pre, max_post;
};
struct segment_tree {
    vector<node> t;
    segment_tree(){};
    segment_tree(int sz) { t.resize(sz << 2 | 1); };
    void pushup(int rt) {
        int ls = rt << 1, rs = rt << 1 | 1;
        t[rt].sum = t[ls].sum + t[rs].sum;
        t[rt].max_sum = max(max(t[ls].max_sum, t[rs].max_sum),
                            t[ls].max_post + t[rs].max_pre);
        t[rt].max_pre = max(t[ls].max_pre, t[ls].sum + t[rs].max_pre);
        t[rt].max_post = max(t[rs].max_post, t[rs].sum + t[ls].max_post);
    }
    void build(const vector<i64>& a, int rt, int l, int r) {
        if (l == r) {
            t[rt].max_sum = t[rt].max_pre = t[rt].max_post = t[rt].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(a, rt << 1, l, mid);
        build(a, rt << 1 | 1, mid + 1, r);
        pushup(rt);
    }
    node query(int rt, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[rt];
        int mid = (l + r) >> 1;
        if (qr <= mid)
            return query(rt << 1, l, mid, ql, qr);
        else if (ql > mid)
            return query(rt << 1 | 1, mid + 1, r, ql, qr);
        else {
            node ans, ls = query(rt << 1, l, mid, ql, qr),
                      rs = query(rt << 1 | 1, mid + 1, r, ql, qr);
            ans.sum = ls.sum + rs.sum;
            ans.max_sum =
                max(max(ls.max_sum, rs.max_sum), ls.max_post + rs.max_pre);
            ans.max_pre = max(ls.max_pre, ls.sum + rs.max_pre);
            ans.max_post = max(rs.max_post, rs.sum + ls.max_post);
            return ans;
        }
    }
};

namespace internal {

std::vector<int> sa_naive(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        if (l == r) return false;
        while (l < n && r < n) {
            if (s[l] != s[r]) return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}

std::vector<int> sa_doubling(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        std::swap(tmp, rnk);
    }
    return sa;
}

// SA-IS, linear-time suffix array construction
// Reference:
// G. Nong, S. Zhang, and W. H. Chan,
// Two Efficient Algorithms for Linear Time Suffix Array Construction
template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper) {
    int n = int(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }
    if (n < THRESHOLD_NAIVE) {
        return sa_naive(s);
    }
    if (n < THRESHOLD_DOUBLING) {
        return sa_doubling(s);
    }

    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper) sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int>& lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n) continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    std::vector<int> lms_map(n + 1, -1);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }

    induce(lms);

    if (m) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (int v : sa) {
            if (lms_map[v] != -1) sorted_lms.push_back(v);
        }
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r]) same = false;
            }
            if (!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa =
            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

}  // namespace internal

std::vector<int> suffix_array(const std::vector<int>& s, int upper) {
    assert(0 <= upper);
    for (int d : s) {
        assert(0 <= d && d <= upper);
    }
    auto sa = internal::sa_is(s, upper);
    return sa;
}

template <class T>
std::vector<int> suffix_array(const std::vector<T>& s) {
    int n = int(s.size());
    std::vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
    std::vector<int> s2(n);
    int now = 0;
    for (int i = 0; i < n; i++) {
        if (i && s[idx[i - 1]] != s[idx[i]]) now++;
        s2[idx[i]] = now;
    }
    return internal::sa_is(s2, now);
}

std::vector<int> suffix_array(const std::string& s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return internal::sa_is(s2, 255);
}

// Reference:
// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications
template <class T>
std::vector<int> lcp_array(const std::vector<T>& s,
                           const std::vector<int>& sa) {
    int n = int(s.size());
    assert(n >= 1);
    std::vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    std::vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0) h--;
        if (rnk[i] == 0) continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}

std::vector<int> lcp_array(const std::string& s, const std::vector<int>& sa) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return lcp_array(s2, sa);
}
template <class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= (V).size(); pw *= 2, ++k) {
            jmp.emplace_back((V).size() - pw * 2 + 1);
            for (int j = 0; j < (jmp[k]).size(); j++)
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);  // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    vector<i64> a(m + 1);
    for (int i = 1; i <= m; i++) cin >> a[i];
    vector<i64> ans(k + 1);
    segment_tree tree(m);
    vector<int> pos((m + 1) * k + 1 + n + 1, 0);
    vector<int> tt((m + 1) * k + 1 + n + 1, 0);
    tree.build(a, 1, 1, m);
    string all = s + "#";
    int sz = all.size();
    for (int i = 0; i < sz - 1; i++) pos[i] = k + 1;
    for (int i = 0; i < sz - 1; i++) tt[i] = i + 1;
    all.reserve(4e6);
    int tp = n + 1;
    for (int i = 1; i <= k; i++) {
        string b;
        cin >> b;
        int now = tp;
        tp += m + 1;
        all += move(b);
        if (i != k) all += "#";
        int noww = tp;
        for (int j = now; j < noww - (i != k); j++)
            pos[j] = i, tt[j] = j - now + 1;
    }
    // cerr << all << endl;
    // for (auto p : pos) cerr << p;
    // ;

    // SuffixArray solve(all);
    auto sa = suffix_array(all);
    auto lcp = lcp_array(all, sa);
    // for (auto p : lcp) cout << p << " ";
    // cout << endl;
    // for (auto p : solve.lcp) cout << p << " ";
    // cout << endl;
    RMQ st(lcp);
    auto get_lcp = [&](int l, int r) {
        // if (l >= r) return 100000;
        return st.query(l, r);
    };

    int R = -1;
    for (int i = 0; i < sa.size(); i++) {
        if (pos[sa[i]] == k + 1) {
            R = i;
        } else {
            if (R == -1) continue;
            int P = pos[sa[i]];
            if (P == 0) continue;
            if (get_lcp(R, i) == 0) {
                continue;
            } else {
                // i64 res = a[tt[sa[i]]];
                // i64 mx = res;
                // for (int j = tt[sa[i]] + 1;
                //      j <= min(m, tt[sa[i]] + get_lcp(R, i) - 1); j++) {
                //     res = res > 0 ? res : 0;
                //     res += a[j];
                //     mx = mx > res ? mx : res;
                // }
                // ans[P] = max(ans[P], mx);
                ans[P] = max(ans[P],
                             tree.query(1, 1, m, tt[sa[i]],
                                        min(m, tt[sa[i]] + get_lcp(R, i) - 1))
                                 .max_sum);
            }
        }
    }
    R = -1;
    for (int i = sa.size() - 1; i >= 0; i--) {
        if (pos[sa[i]] == k + 1) {
            R = i;
        } else {
            // cout << R << " " << i << endl;
            if (R == -1) continue;
            int P = pos[sa[i]];
            if (P == 0) continue;
            if (get_lcp(i, R) == 0 || R == i) {
                continue;
            } else {
                ans[P] = max(ans[P],
                             tree.query(1, 1, m, tt[sa[i]],
                                        min(tt[sa[i]] + get_lcp(i, R) - 1, m))
                                 .max_sum);
            }
        }
    }

    for (int i = 1; i <= k; i++) cout << ans[i] << '\n';
}
/*
5 5 5
uqusa
-9 -7 8 -8 -3
saimh
qusam
qusaf
ubgxj
uquxw
*/
