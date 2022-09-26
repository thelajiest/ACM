#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
template <int mod>
struct mint {
    int x;
    mint() : x(0) {}
    mint(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    mint &operator+=(const mint &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator-=(const mint &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator*=(const mint &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }
    mint &operator/=(const mint &p) {
        *this *= p.inverse();
        return *this;
    }
    mint operator-() const { return mint(-x); }
    mint operator+(const mint &p) const { return mint(*this) += p; }
    mint operator-(const mint &p) const { return mint(*this) -= p; }
    mint operator*(const mint &p) const { return mint(*this) *= p; }
    mint operator/(const mint &p) const { return mint(*this) /= p; }
    bool operator==(const mint &p) const { return x == p.x; }
    bool operator!=(const mint &p) const { return x != p.x; }
    mint inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return mint(u);
    }
    friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }
    friend istream &operator>>(istream &is, mint &a) {
        int64_t t;
        is >> t;
        a = mint<mod>(t);
        return (is);
    }
    int get() const { return x; }
    static constexpr int get_mod() { return mod; }
};

template <class Z, int rt>
struct NTT {
    vector<int> rev;
    vector<Z> roots{0, 1};
    void dft(vector<Z> &a) {
        int n = a.size();

        if (int(rev.size()) != n) {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; i++) {
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
            }
        }

        for (int i = 0; i < n; i++) {
            if (rev[i] < i) {
                swap(a[i], a[rev[i]]);
            }
        }
        if (int(roots.size()) < n) {
            int k = __builtin_ctz(roots.size());
            roots.resize(n);
            while ((1 << k) < n) {
                Z e = power(Z(rt), (Z::get_mod() - 1) >> (k + 1));
                for (int i = 1 << (k - 1); i < (1 << k); i++) {
                    roots[2 * i] = roots[i];
                    roots[2 * i + 1] = roots[i] * e;
                }
                k++;
            }
        }
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    Z u = a[i + j];
                    Z v = a[i + j + k] * roots[k + j];
                    a[i + j] = u + v;
                    a[i + j + k] = u - v;
                }
            }
        }
    }
    void idft(vector<Z> &a) {
        int n = a.size();
        reverse(a.begin() + 1, a.end());
        dft(a);
        Z inv = (1 - Z::get_mod()) / n;
        for (int i = 0; i < n; i++) {
            a[i] *= inv;
        }
    }
    vector<Z> multiply(vector<Z> a, vector<Z> b) {
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot) {
            sz *= 2;
        }

        a.resize(sz), b.resize(sz);
        dft(a), dft(b);

        for (int i = 0; i < sz; ++i) {
            a[i] = a[i] * b[i];
        }

        idft(a);
        a.resize(tot);
        return a;
    }
};

template <class Z, int rt>
struct Poly {
    vector<Z> a;
    Poly() {}
    Poly(int sz, Z val) { a.assign(sz, val); }
    Poly(const vector<Z> &a) : a(a) {}
    Poly(const initializer_list<Z> &a) : a(a) {}
    int size() const { return a.size(); }
    void resize(int n) { a.resize(n); }
    Z operator[](int idx) const {
        if (idx < size()) {
            return a[idx];
        } else {
            return 0;
        }
    }
    Z &operator[](int idx) { return a[idx]; }
    Poly mulxk(int k) const {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const {
        k = min(k, size());
        return Poly(vector<Z>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {
        if (size() <= k) {
            return Poly();
        }
        return Poly(vector<Z>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly &a, const Poly &b) {
        vector<Z> res(max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] + b[i];
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &a, const Poly &b) {
        vector<Z> res(max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] - b[i];
        }
        return Poly(res);
    }

    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        static NTT<Z, rt> ntt;
        return ntt.multiply(a.a, b.a);
    }
    friend Poly operator*(Z a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }
    friend Poly operator*(Poly a, Z b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }
    Poly &operator+=(Poly b) { return (*this) = (*this) + b; }
    Poly &operator-=(Poly b) { return (*this) = (*this) - b; }
    Poly &operator*=(Poly b) { return (*this) = (*this) * b; }
};
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int mod = 998244353;
    using Z = mint<mod>;
    using poly = Poly<Z, 3>;
    int n;
    cin >> n;

    vector<vector<int>> t(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        t[i].push_back(p);
        t[p].push_back(i);
    }

    vector<int> siz(n + 1), son(n + 1), f(n + 1);

    function<void(int, int)> dfs = [&](int u, int fa) {
        siz[u] = 1;
        f[u] = fa;
        for (auto v : t[u]) {
            if (v == fa) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    };
    dfs(1, 0);
    vector<poly> dp(n + 1);
    function<void(int)> dfs2 = [&](int u) {
        vector<int> lt;
        int now = u;
        while (now) {
            lt.push_back(now);
            now = son[now];
        }
        for (auto it : lt) {
            vector<poly> res;
            for (auto v : t[it]) {
                if (v == f[it] || v == son[it]) continue;
                dfs2(v);
                res.emplace_back(std::move(dp[v]));
                res.rbegin()->resize(res.rbegin()->size() + 1);
            }
            function<poly(int, int)> dc = [&](int l, int r) -> poly {
                if (r - l <= 1) {
                    if (l == r) return {1, 0};
                    return res[l];
                }
                int mid = (l + r) / 2;
                return dc(l, mid) * dc(mid, r);
            };
            dp[it] = dc(0, res.size());
        }
        vector<poly> res;
        for (auto &&it : lt) res.emplace_back(std::move(dp[it]));

        function<pair<poly, poly>(int, int)> dc2 =
            [&](int l, int r) -> pair<poly, poly> {
            if (r - l == 1) {
                return {{0, 1}, res[l]};
            }
            int mid = (l + r) / 2;
            auto [al, bl] = dc2(l, mid);
            auto [ar, br] = dc2(mid, r);
            return {ar * bl + al, bl * br};
        };

        auto [x, y] = dc2(0, res.size());
        dp[u] = x + y;
        dp[u].resize(dp[u].size() + 1);
    };
    dfs2(1);
    for (int i = 1; i <= n; i++) cout << dp[1][i] << '\n';

    return 0;
}