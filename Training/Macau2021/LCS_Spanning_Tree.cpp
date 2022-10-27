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

    SuffixArrayFast(const T &vs) {
        vector<int> new_vs(vs.size() + 1);

        auto d = *min_element(vs.begin(), vs.end());
        for (int i = 0; i < (int)vs.size(); i++) {
            new_vs[i] = vs[i] - d + 1;
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

struct unionfind {
    vector<int> p;
    unionfind(int N) { p = vector<int>(N, -1); }
    int root(int x) {
        if (p[x] < 0) {
            return x;
        } else {
            p[x] = root(p[x]);
            return p[x];
        }
    }
    bool same(int x, int y) { return root(x) == root(y); }
    void unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (p[x] < p[y]) {
                swap(x, y);
            }
            p[y] += p[x];
            p[x] = y;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> s(n);
    vector<int> comb;

    int now = 26;
    for (auto &it : s) {
        string res;
        cin >> res;
        for (auto p : res) it.push_back(p - 'a');
        it.push_back(now);
        now++;
        copy(it.begin(), it.end(), back_inserter(comb));
    }

    SuffixArrayFast<vector<int>> Sa(comb);
    vector<int> pos(comb.size());

    int n_comb = comb.size();

    unionfind uf(n);

    for (int i = 0, cnt = 0; i < n_comb; cnt++) {
        for (int t = 0; t < int(s[cnt].size()); t++, i++) {
            pos[i] = cnt;
        }
    }
    vector<array<int, 3>> edge;

    int lst = Sa.sa[0];
    for (int i = 0, j; i < n_comb; i = j) {
        j = i;
        int lcp = Sa.lc[Sa.rk[lst]];
        while (j < n_comb && pos[Sa.sa[j]] == pos[Sa.sa[i]]) {
            if (pos[Sa.sa[j]] != pos[lst])
                edge.push_back({pos[Sa.sa[j]], pos[lst], lcp});
            if (j < Sa.lc.size()) lcp = min(lcp, Sa.lc[j]);
            j++;
        }
        lst = Sa.sa[j - 1];
    }
    lst = Sa.sa.back();
    for (int i = n_comb - 2, j; i >= 0; i = j) {
        j = i;
        int lcp = Sa.lc[i];
        while (j >= 0 && pos[Sa.sa[j]] == pos[Sa.sa[i]]) {
            if (pos[Sa.sa[j]] != pos[lst])
                edge.push_back({pos[Sa.sa[j]], pos[lst], lcp});
            j--;
            lcp = min(lcp, Sa.lc[j]);
        }
        lst = Sa.sa[j + 1];
    }

    i64 ans = 0;
    sort(edge.begin(), edge.end(),
         [&](array<int, 3> &a, array<int, 3> &b) { return a[2] > b[2]; });

    for (auto [u, v, w] : edge) {
        assert(u != v);
        if (uf.same(u, v))
            continue;
        else {
            uf.unite(u, v);
            ans += w;
        }
    }

    cout << ans << endl;
    return 0;
}