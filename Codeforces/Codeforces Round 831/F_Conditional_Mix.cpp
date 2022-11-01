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
    Poly operator/(const Poly &r) const { return Poly(this->a) /= r; }
    Poly rev(int deg = -1) const {
        Poly ret(this->a);
        if (deg != -1) ret.a.resize(deg, Z(0));
        reverse(begin(ret.a), end(ret.a));
        return ret;
    }
    Poly &operator/=(const Poly &r) {
        if (this->size() < r.size()) {
            this->a.clear();
            return *this;
        }
        int n = this->size() - r.size() + 1;
        return *this = (rev().modxk(n) * r.rev().inv(n)).modxk(n).rev(n);
    }
    Poly deriv() const {
        if (a.empty()) {
            return Poly();
        }
        vector<Z> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i) {
            res[i] = Z(i + 1) * a[i + 1];
        }
        return Poly(res);
    }
    Poly integr() const {
        vector<Z> res(size() + 1);
        for (int i = 0; i < size(); ++i) {
            res[i + 1] = a[i] / (i + 1);
        }
        return Poly(res);
    }
    Poly inv(int m) const {
        Poly x{a[0].inverse()};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const { return (deriv() * inv(m)).integr().modxk(m); }
    Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly pow(int k, int m) const {
        int i = 0;
        while (i < size() && a[i].get() == 0) {
            i++;
        }
        if (i == size() || 1LL * i * k >= m) {
            return Poly(vector<Z>(m));
        }
        Z v = a[i];
        auto f = divxk(i) * v.inverse();
        return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * power(v, k);
    }
    Poly sqrt(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((Z::get_mod() + 1) / 2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        reverse(b.a.begin(), b.a.end());
        return ((*this) * b).divxk(n - 1);
    }
    vector<Z> eval(vector<Z> x) const {
        if (size() == 0) {
            return vector<Z>(x.size(), 0);
        }
        const int n = max(int(x.size()), size());
        vector<Poly> q(4 * n);
        vector<Z> ans(x.size());
        x.resize(n);
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        function<void(int, int, int, const Poly &)> work =
            [&](int p, int l, int r, const Poly &num) {
                if (r - l == 1) {
                    if (l < int(ans.size())) {
                        ans[l] = num[0];
                    }
                } else {
                    int m = (l + r) / 2;
                    work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
                    work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
                }
            };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
    Poly inter(const Poly &y) const {
        vector<Poly> Q(a.size() * 4), P(a.size() * 4);
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            int m = (l + r) >> 1;
            if (l == r) {
                Q[p] = Poly{-a[m], Z(1)};
            } else {
                build(p * 2, l, m);
                build(p * 2 + 1, m + 1, r);
                Q[p] = Q[p * 2] * Q[p * 2 + 1];
            }
        };
        build(1, 0, a.size() - 1);
        Poly f;
        f.a.resize((int)(Q[1].size()) - 1);
        for (int i = 0; i + 1 < Q[1].size(); i += 1)
            f[i] = (Q[1][i + 1] * (i + 1));
        Poly g = f.eval(a);
        function<void(int, int, int)> work = [&](int p, int l, int r) {
            int m = (l + r) >> 1;
            if (l == r) {
                P[p].a.push_back(y[m] * power(g[m], Z::get_mod() - 2));
                return;
            }
            work(p * 2, l, m);
            work(p * 2 + 1, m + 1, r);
            P[p].a.resize(r - l + 1);
            Poly A = P[p * 2] * Q[p * 2 + 1];
            Poly B = P[p * 2 + 1] * Q[p * 2];
            for (int i = 0; i <= r - l; i++) P[p][i] = (A[i] + B[i]);
        };
        work(1, 0, a.size() - 1);
        return P[1];
    }
    Poly shift(Z t, int m = -1) {
        /*
            input: y(0) , y(1) , ... , y(n-1)
            output: y(t) , t(t+1) , ... ,y (t+m-1)
            ## m = -1 => m = n
        */
        if (m == -1) m = this->size();
        i64 T = t.get();
        int k = (int)(this->size()) - 1;
        T %= Z::get_mod();

        if (T <= k) {
            Poly ret(m, 0);
            int ptr = 0;
            for (i64 i = T; i <= k && ptr < m; i++) ret[ptr++] = a[i];
            if (k + 1 < T + m) {
                auto suf = shift(k + 1, m - ptr);
                for (int i = k + 1; i < T + m; i++)
                    ret[ptr++] = suf[i - (k + 1)];
            }
            return ret;
        }
        if (T + m > Z::get_mod()) {
            auto pref = shift(T, Z::get_mod() - T);
            auto suf = shift(0, m - pref.size());
            copy(begin(suf.a), end(suf.a), back_inserter(pref.a));
            return pref;
        }

        Poly finv(k + 1, 1), d(k + 1, 0);
        for (int i = 2; i <= k; i++) finv[k] *= i;
        finv[k] = Z(1) / finv[k];
        for (int i = k; i >= 1; i--) finv[i - 1] = finv[i] * i;
        for (int i = 0; i <= k; i++) {
            d[i] = finv[i] * finv[k - i] * a[i];
            if ((k - i) & 1) d[i] = -d[i];
        }

        Poly h(m + k, 0);
        for (int i = 0; i < m + k; i++) {
            h[i] = Z(1) / (T - k + i);
        }

        auto dh = d * h;
        Poly ret(m, 0);
        Z cur = T;
        for (int i = 1; i <= k; i++) cur *= T - i;
        for (int i = 0; i < m; i++) {
            ret[i] = cur * dh[k + i];
            cur *= T + i + 1;
            cur *= h[i];
        }
        return ret;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }

    int g = 0;
    for (auto [x, cnt] : mp) g = max(g, cnt);
    constexpr int mod = 998244353;
    using Z = mint<mod>;
    using poly = Poly<Z, 3>;
    auto solve = [&](int x) -> Z {
        if (x == 0) return 0;
        poly ans;
        for (int t = 1; t <= x; t++) {
            poly res(t + 1, 0);
            res[0] = 1;
            res[t] = Z(-1);
            res = res.log(n + 1);
            ans = ans + res;
        }
        for (auto &it : ans.a) it = -it;
        ans = ans.exp(n + 1);
        return ans[n];
    };
    Z ans = solve(n);
    cout << ans << endl;
    for (auto [x, cnt] : mp) {
        ans -= solve(cnt - 1);
    }
    cout << ans << endl;

    return 0;
}