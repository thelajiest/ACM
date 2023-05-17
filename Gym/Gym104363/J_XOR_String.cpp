#include <bits/stdc++.h>

using i64 = std::int64_t;

template <class T>
struct SuffixArrayFast {
    int n;
    std::vector<int> sa, rk, lc;

    std::vector<int> sa_is(const std::vector<int> &s) const {
        const int n = (int)s.size();
        std::vector<int> ret(n);

        std::vector<int> is_s(n), is_lms(n);
        int m = 0;
        for (int i = n - 2; i >= 0; i--) {
            is_s[i] = (s[i] > s[i + 1]) or (s[i] == s[i + 1] and is_s[i + 1]);
            m += (is_lms[i + 1] = is_s[i] and not is_s[i + 1]);
        }

        auto induced_sort = [&](const std::vector<int> &lms) {
            int upper = *(std::max_element(s.begin(), s.end()));
            std::vector<int> l(upper + 2), r(upper + 2);
            for (auto &&v : s) {
                ++l[v + 1];
                ++r[v];
            }
            std::partial_sum(l.begin(), l.end(), l.begin());
            std::partial_sum(r.begin(), r.end(), r.begin());
            std::fill(ret.begin(), ret.end(), -1);
            for (int i = (int)lms.size() - 1; i >= 0; i--) {
                ret[--r[s[lms[i]]]] = lms[i];
            }
            for (auto &&v : ret) {
                if (v >= 1 and is_s[v - 1]) ret[l[s[v - 1]]++] = v - 1;
            }
            std::fill(r.begin(), r.end(), 0);
            for (auto &&v : s) ++r[v];
            std::partial_sum(r.begin(), r.end(), r.begin());
            for (int k = (int)ret.size() - 1, i = ret[k]; k >= 1;
                 i = ret[--k]) {
                if (i >= 1 and not is_s[i - 1]) {
                    ret[--r[s[i - 1]]] = i - 1;
                }
            }
        };

        std::vector<int> lms;
        lms.reserve(m);
        for (int i = 1; i < n; i++) {
            if (is_lms[i]) lms.push_back(i);
        }

        induced_sort(lms);

        std::vector<int> new_lms;
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
            std::vector<int> new_s(m);
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
        std::vector<int> new_vs(vs.size() + 1);

        auto d = *(std::min_element(vs.begin(), vs.end()));
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
template <typename T>
std::pair<std::vector<std::vector<int>>, int> CartesianTree(std::vector<T> &a) {
    int N = (int)a.size();
    std::vector<std::vector<int>> g(N);
    std::vector<int> p(N, -1), st;
    st.reserve(N);
    for (int i = 0; i < N; i++) {
        int prv = -1;
        while (!st.empty() && a[i] < a[st.back()]) {
            prv = st.back();
            st.pop_back();
        }
        if (prv != -1) p[prv] = i;
        if (!st.empty()) p[i] = st.back();
        st.push_back(i);
    }
    int root = -1;
    for (int i = 0; i < N; i++) {
        if (p[i] != -1)
            g[p[i]].push_back(i);
        else
            root = i;
    }
    return std::make_pair(g, root);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    int N = s.size();
    s = s + s;
    SuffixArrayFast SA(s);

    std::vector<int> val(N);
    for (int i = 0; i < N; i++) {
        std::cin >> val[i];
    }

    std::vector<int> dval(2 * N, 0);
    for (int i = 0; i < 2 * N; i++) {
        if (SA.sa[i] < N) dval[i] = val[SA.sa[i]];
    }

    int ans = 0;
    for (int i = 0; i < 2 * N - 1; i++) {
        if (SA.sa[i] < N && dval[i] == 0 && SA.lc[i] < N) {
            if (i == 0 || SA.lc[i - 1] < N) ans = std::max(ans, N);
        }
    }
    for (int i = 1; i < 2 * N; i++) {
        dval[i] ^= dval[i - 1];
    }
    auto qXor = [&](int l, int r) -> int {
        // [l,r]
        if (l == 0) return dval[r];
        return dval[r] ^ dval[l - 1];
    };

    auto [CTree, root] = CartesianTree(SA.lc);

    std::vector<std::pair<int, int>> internal(SA.lc.size());

    auto dfs = [&](auto &&self, int u) -> void {
        internal[u] = {u, u};
        for (const auto &v : CTree[u]) {
            self(self, v);
            internal[u].first = std::min(internal[u].first, internal[v].first);
            internal[u].second =
                std::max(internal[u].second, internal[v].second);
        }
        auto [L, R] = internal[u];
        R++;
        int len = SA.lc[u];
        int Xor = qXor(L, R);
        if (Xor == 0 && SA.lc[u] <= N) {
            ans = std::max(ans, len);
        }
    };

    dfs(dfs, root);

    std::cout << ans << std::endl;

    return 0;
}