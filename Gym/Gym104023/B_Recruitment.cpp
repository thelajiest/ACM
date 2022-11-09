#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
#define int i64
vector<int> primes;

vector<int> prime_sieve(int N) {
    vector<bool> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}

template <class T>
vector<T> OsakDivisors(T x) {
    vector<pair<T, int>> lt;
    for (auto p : primes) {
        if (1LL * p * p > x) break;
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        if (cnt >= 1) lt.emplace_back(p, cnt);
    }
    if (x > 1) lt.emplace_back(x, 1);
    vector<T> div;
    auto dfs = [&](auto rec, int i, T c) {
        if (i == int(lt.size())) {
            div.push_back(c);
            return;
        }
        for (int j = 0; j <= lt[i].second; j++) {
            rec(rec, i + 1, c);
            c *= lt[i].first;
        }
    };
    dfs(dfs, 0, 1);
    return div;
}
struct UnionFind {
    vector<int> data;
    UnionFind(int N) : data(N, -1) {}

    int find(int k) { return data[k] < 0 ? k : data[k] = find(data[k]); }

    int unite(int x, int y) {
        if ((x = find(x)) == (y = find(y))) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    // f ... merge function
    template <typename F>
    int unite(int x, int y, const F &f) {
        if ((x = find(x)) == (y = find(y))) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        f(x, y);
        return true;
    }

    int size(int k) { return -data[find(k)]; }

    int same(int x, int y) { return find(x) == find(y); }
};

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    primes = prime_sieve(sqrt(*max_element(s.begin(), s.end())) + 10);

    vector<vector<vector<int>>> st{{{s.back()}}};

    int ones = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] - s[i + 1] == 1) {
            ones++;
            continue;
        }
        set<vector<int>> se;
        for (auto state : st.back()) {
            for (int x : state) {
                auto divX = OsakDivisors(x);
                for (auto p : divX) {
                    int q = x / p;
                    if (s[i + 1] - x == s[i] - p - q) {
                        vector<int> res;
                        for (auto it : state) {
                            if (it == x) {
                                res.push_back(p);
                                res.push_back(q);
                            } else
                                res.push_back(it);
                        }
                        if (res.size() == n - i) se.insert(res);
                    }
                }
            }
        }
        st.push_back({se.begin(), se.end()});
    }
    if (st.back().size() == 0 && ones != n) {
        cout << "-1";
        return 0;
    }
    auto ans = *st.back().begin();
    int t = ans.size();
    for (auto p : ans) {
        cout << p << " ";
    }
    int pos = t;
    while (ones--) {
        cout << 1 << " ";
        ans.push_back(1);
    }
    assert(ans.size() == n);
    UnionFind uf(t);
    cout << '\n';
    vector<int> out;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] - s[i + 1] == 1) {
            out.push_back(pos++);
        } else {
            for (int j = 0; j < t - 1; j++) {
                int tt = 0;
                if ((s[i] - ans[j] - ans[j + 1] ==
                     s[i + 1] - ans[j] * ans[j + 1]) &&
                    (!uf.same(j, j + 1))) {
                    out.push_back(j + 1);
                    int prod = ans[j] * ans[j + 1];
                    for (int k = 0; k < t; k++)
                        if (uf.same(j, k)) ans[k] = prod;
                    for (int k = 0; k < t; k++)
                        if (uf.same(j + 1, k)) ans[k] = prod;
                    uf.unite(j, j + 1);
                    tt++;
                    break;
                }
                assert(tt <= 1);
            }
        }
    }
    assert(out.size() == n - 1);
    for (auto p : out) cout << p << '\n';

    return 0;
}