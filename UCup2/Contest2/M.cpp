#include <bits/stdc++.h>

using i64 = std::int64_t;

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

struct KMPAutomaton {
    std::vector<int> fail;
    std::vector<std::array<int, 26>> tr;
    KMPAutomaton(const std::string &s) {
        tr.resize(std::size(s) + 1);
        for (int i = 0; i < (int)s.size(); i++) {
            tr[i][s[i] - 'a'] = i + 1;
        }
    };

    void build() {
        fail.resize(this->tr.size());
        std::queue<int> Q;
        for (int i = 0; i < 26; i++)
            if (this->tr[0][i]) Q.push(this->tr[0][i]);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0; i < 26; i++) {
                if (this->tr[u][i])
                    fail[this->tr[u][i]] = this->tr[fail[u]][i],
                    Q.push(this->tr[u][i]);
                else
                    this->tr[u][i] = this->tr[fail[u]][i];
            }
        }
        return;
    }
};

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
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return mint(u);
    }
    friend std::ostream &operator<<(std::ostream &os, const mint &p) {
        return os << p.x;
    }
    friend std::istream &operator>>(std::istream &is, mint &a) {
        int64_t t;
        is >> t;
        a = mint<mod>(t);
        return (is);
    }
    int get() const { return x; }
    static constexpr int get_mod() { return mod; }
};

constexpr int P = 998244353;
using Z = mint<P>;

template <class Z>
struct NTT {
    std::vector<int> rev;
    std::vector<Z> roots{0, 1};

    static constexpr int getRoot() {
        auto _mod = Z::get_mod();
        using u64 = uint64_t;
        u64 ds[32] = {};
        int idx = 0;
        u64 m = _mod - 1;
        for (u64 i = 2; i * i <= m; ++i) {
            if (m % i == 0) {
                ds[idx++] = i;
                while (m % i == 0) m /= i;
            }
        }
        if (m != 1) ds[idx++] = m;

        int _pr = 2;
        for (;;) {
            int flg = 1;
            for (int i = 0; i < idx; ++i) {
                u64 a = _pr, b = (_mod - 1) / ds[i], r = 1;
                for (; b; a = a * a % _mod, b /= 2) {
                    if (b % 2 == 1) r = r * a % _mod;
                }
                if (r == 1) {
                    flg = 0;
                    break;
                }
            }
            if (flg == 1) break;
            ++_pr;
        }
        return _pr;
    };

    static constexpr int rt = getRoot();

    void dft(std::vector<Z> &a) {
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
                std::swap(a[i], a[rev[i]]);
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
    void idft(std::vector<Z> &a) {
        int n = a.size();
        reverse(a.begin() + 1, a.end());
        dft(a);
        Z inv = (1 - Z::get_mod()) / n;
        for (int i = 0; i < n; i++) {
            a[i] *= inv;
        }
    }
    std::vector<Z> multiply(std::vector<Z> a, std::vector<Z> b) {
        int sz = 1, tot = a.size() + b.size() - 1;

        if (tot <= 20) {
            std::vector<Z> ret(tot);
            for (size_t i = 0; i < a.size(); i++)
                for (size_t j = 0; j < b.size(); j++) ret[i + j] += a[i] * b[j];
            return ret;
        }

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

template <class Z>
struct Poly {
    std::vector<Z> a;
    Poly() {}
    Poly(int sz, Z val) { a.assign(sz, val); }
    Poly(const std::vector<Z> &a) : a(a) {}
    Poly(const std::initializer_list<Z> &a) : a(a) {}
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
        k = std::min(k, size());
        return Poly(std::vector<Z>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {
        if (size() <= k) {
            return Poly();
        }
        return Poly(std::vector<Z>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] + b[i];
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] - b[i];
        }
        return Poly(res);
    }

    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        static NTT<Z> ntt;
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
        std::vector<Z> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i) {
            res[i] = Z(i + 1) * a[i + 1];
        }
        return Poly(res);
    }
    Poly integr() const {
        std::vector<Z> res(size() + 1);
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
            return Poly(std::vector<Z>(m));
        }
        Z v = a[i];
        auto f = divxk(i) * v.inverse();
        return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * power(v, k);
    }
};

template <class Z>
Z CoeffofRationalFunction(Poly<Z> P, Poly<Z> Q, i64 k) {
    Z ret = 0;
    if (P.size() >= Q.size()) {
        auto R = P / Q;
        P -= R * Q;
        while (P.size() && P.a.back() == Z(0)) P.a.pop_back();
        if (k < int(R.size())) ret += R[k];
    }
    if (P.a.empty()) return ret;
    P.a.resize(int(Q.size()) - 1);

    while (k > 0) {
        Poly<Z> Q2(Q.a);
        for (int i = 1; i < int(Q2.size()); i += 2) Q2[i] = -Q2[i];
        auto sub = [&](const Poly<Z> &as, bool odd) {
            Poly<Z> bs((as.size() + !odd) / 2, 0);
            for (int i = odd; i < (int)as.size(); i += 2) bs[i >> 1] = as[i];
            return bs;
        };
        P = sub(P * Q2, k & 1);
        Q = sub(Q * Q2, 0);
        k /= 2;
    }

    return ret + P[0];
}
template <class Z>
Z LinearlyRecurrent(const Poly<Z> &a, Poly<Z> c, i64 k) {
    /*
        a_n=\sum_{d=1^t} c_d * a_{n-d}
        give a_0,a_1,...,a_{t-1}
        c_1,c_2,...,c_t[but store at cp[0,...,t-1]]
        solev a_k
        TC: O(t\logt\logk)
    */
    assert(a.size() == c.size());
    c = Poly<Z>{1} - c.mulxk(1);
    return CoeffofRationalFunction<Z>((a * c).modxk(a.size()), c, k);
}

template <typename Z>
std::vector<Z> BerlekampMassey(const std::vector<Z> &s) {
    const int N = (int)s.size();
    std::vector<Z> b, c;
    b.reserve(N + 1);
    c.reserve(N + 1);
    b.push_back(Z(1));
    c.push_back(Z(1));
    Z y = Z(1);
    for (int ed = 1; ed <= N; ed++) {
        int l = int(c.size()), m = int(b.size());
        Z x = 0;
        for (int i = 0; i < l; i++) x += c[i] * s[ed - l + i];
        b.emplace_back(Z(0));
        m++;
        if (x == Z(0)) continue;
        Z freq = x / y;
        if (l < m) {
            auto tmp = c;
            c.insert(begin(c), m - l, Z(0));
            for (int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];
            b = tmp;
            y = x;
        } else {
            for (int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];
        }
    }
    std::reverse(begin(c), end(c));
    return c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::string s;
    std::cin >> s;

    std::reverse(begin(s), end(s));

    KMPAutomaton am(s);
    am.build();
    auto adx = am.tr;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (adx[i][j] == n) adx[i][j] = -1;
        }
    }

    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j < 26; j++) std::cerr << adx[i][j] << " ";
    //     std::cerr << std::endl;
    // }
    std::vector<Z> vec(n + 1, Z(1));

    auto multiply = [&](const decltype(adx) &matrix, const std::vector<Z> &v) {
        std::vector<Z> ret(vec.size(), 0);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 26; j++) {
                if (matrix[i][j] != -1) ret[i] += v[matrix[i][j]];
            }
        }
        return ret;
    };

    std::vector<Z> f{Z(1)};

    for (int i = 0; i < 2 * n; i++) {
        vec = multiply(adx, vec);
        f.push_back(vec[n]);
    }

    // for (const auto &v : f) std::cerr << v << std::endl;

    NTT<Z> ntt;
    auto bm = BerlekampMassey<Z>(f);

    bm = {bm.begin() + 1, bm.end()};

    for (auto &v : bm) v = -v;
    for (auto &v : bm) std::cerr << v << std::endl;
    f.resize(bm.size());
    auto ans = LinearlyRecurrent<Z>(f, bm, m - n);

    std::cout << ans << std::endl;
    return 0;
}