#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <class T>
struct SuffixArrayFast {
    int n;
    vector<int> sa, rk, lc;

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

    SuffixArrayFast(const T &vs, bool compress = false) {
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
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    string comb = s + s + t + t;
    SuffixArrayFast<string> SA(comb);

    int sz = SA.n;
    i64 ans = 0;
    int fst = 0;
    for (int l = 0, r; l < sz; l = r + 1) {
        r = l;
        while (r < sz - 1 and SA.lc[r] >= n) r++;
        for (int i = l; i <= r; i++) {
            if (0 <= SA.sa[i] && SA.sa[i] < n) fst++;
        }
        for (int i = l; i <= r; i++) {
            if (2 * n <= SA.sa[i] && SA.sa[i] < 3 * n) ans += fst;
        }
    }

    cout << ans << endl;

    return 0;
}
