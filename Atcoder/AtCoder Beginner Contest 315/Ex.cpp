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
struct relaxed_convolution {
    int N;
    std::vector<Z> A, B, C;
    NTT<Z> convolution;
    relaxed_convolution() : N(0) {}
    Z query(Z a, Z b) {
        A.push_back(a);
        B.push_back(b);
        C.push_back(0);
        if (N > 0) {
            C.push_back(0);
        }
        int p = __builtin_ctz(N + 2);
        for (int j = 0; j <= p; j++) {
            std::vector<Z> a1(1 << j);
            for (int k = 0; k < (1 << j); k++) {
                a1[k] = A[(1 << j) - 1 + k];
            }
            std::vector<Z> b1(1 << j);
            for (int k = 0; k < (1 << j); k++) {
                b1[k] = B[N - ((1 << j) - 1 - k)];
            }
            std::vector<Z> c1 = convolution.multiply(a1, b1);
            for (int k = 0; k < (1 << (j + 1)) - 1; k++) {
                C[N + k] += c1[k];
            }
            if ((1 << p) == N + 2 && j == p - 1) {
                break;
            }
            std::vector<Z> a2(1 << j);
            for (int k = 0; k < (1 << j); k++) {
                a2[k] = A[N - ((1 << j) - 1 - k)];
            }
            std::vector<Z> b2(1 << j);
            for (int k = 0; k < (1 << j); k++) {
                b2[k] = B[(1 << j) - 1 + k];
            }
            std::vector<Z> c2 = convolution.multiply(a2, b2);
            for (int k = 0; k < (1 << (j + 1)) - 1; k++) {
                C[N + k] += c2[k];
            }
        }
        N++;
        return C[N - 1];
    }
};

constexpr int P = 998244353;
using Z = mint<P>;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    relaxed_convolution<Z> rc;

    int n;
    std::cin >> n;

    std::vector<Z> F(n + 1);
    F[0] = 1;

    Z sum = 0;
    for (int i = 1; i <= n; i++) {
        auto now = rc.query(F[i - 1], F[i - 1]);
        Z A;
        std::cin >> A;
        sum += now;
        F[i] = sum * A;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << F[i] << " \n"[i == n];
    }

    return 0;
}
