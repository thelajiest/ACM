#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define re
#define gc get_char
#define cs const

namespace IO {
inline char get_char() {
    static cs int Rlen = 1 << 20 | 1;
    static char buf[Rlen], *p1, *p2;
    return (p1 == p2) &&
                   (p2 = (p1 = buf) + fread(buf, 1, Rlen, stdin), p1 == p2)
               ? EOF
               : *p1++;
}

inline int getint() {
    re char c;

    while (!isdigit(c = gc()))
        ;

    re int num = c ^ 48;

    while (isdigit(c = gc())) num = (num + (num << 2) << 1) + (c ^ 48);

    return num;
}
}  // namespace IO
using namespace IO;

cs int mod = 998244353, N = 410000, inv2 = mod + 1 >> 1;
inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
inline int dec(int a, int b) { return a < b ? a - b + mod : a - b; }
inline int mul(int a, int b) { return (ll)a * b % mod; }
inline int quickpow(int a, int b, int res = 1) {
    while (b) {
        if (b & 1) res = mul(res, a);

        a = mul(a, a);
        b >>= 1;
    }

    return res;
}

typedef vector<int> Poly;

inline void print(cs Poly &a, char c = ' ', ostream &out = cout) {
    for (int re i = 1; i < a.size(); ++i) out << a[i] << c;
}

int r[N], inv[N];
inline void NTT(Poly &A, int len, int typ) {
    for (int re i = 0; i < len; ++i)
        if (i < r[i]) swap(A[i], A[r[i]]);

    for (int re i = 1; i < len; i <<= 1) {
        int wn = quickpow(typ == -1 ? (mod + 1) / 3 : 3, (mod - 1) / i / 2);

        for (int re j = 0; j < len; j += i << 1)
            for (int re k = 0, x, y, w = 1; k < i; ++k, w = mul(w, wn)) {
                x = A[j + k], y = mul(w, A[j + k + i]);
                A[j + k] = add(x, y);
                A[j + k + i] = dec(x, y);
            }
    }

    if (typ == -1)
        for (int re i = 0; i < len; ++i) A[i] = mul(A[i], inv[len]);
}
inline void init_rev(int len) {
    for (int re i = 0; i < len; ++i)
        r[i] = r[i >> 1] >> 1 | ((i & 1) * (len >> 1));
}

inline Poly operator+(cs Poly &a, cs Poly &b) {
    Poly c = a;
    c.resize(max(a.size(), b.size()));

    for (int re i = 0; i < b.size(); ++i) c[i] = add(c[i], b[i]);

    return c;
}

inline Poly operator-(cs Poly &a, cs Poly &b) {
    Poly c = a;
    c.resize(max(a.size(), b.size()));

    for (int re i = 0; i < b.size(); ++i) c[i] = dec(c[i], b[i]);

    return c;
}

inline Poly operator*(Poly a, Poly b) {
    int n = a.size(), m = b.size(), l = 1;

    while (l < n + m - 1) l <<= 1;

    init_rev(l);
    a.resize(l), NTT(a, l, 1);
    b.resize(l), NTT(b, l, 1);

    for (int re i = 0; i < l; ++i) a[i] = mul(a[i], b[i]);

    NTT(a, l, -1);
    a.resize(n + m - 1);
    return a;
}

inline Poly operator*(Poly a, int b) {
    for (int re i = 0; i < a.size(); ++i) a[i] = mul(a[i], b);

    return a;
}

inline Poly Deriv(Poly a) {
    for (int re i = 0; i + 1 < a.size(); ++i) a[i] = mul(a[i + 1], i + 1);

    a.pop_back();
    return a;
}

inline Poly Integ(Poly a) {
    a.push_back(0);

    for (int re i = a.size() - 1; i; --i) a[i] = mul(a[i - 1], inv[i]);

    a[0] = 0;
    return a;
}

inline Poly Inv(cs Poly &a, int lim) {
    Poly c, b(1, quickpow(a[0], mod - 2));

    for (int re l = 4; (l >> 2) < lim; l <<= 1) {
        init_rev(l);
        c = a, c.resize(l >> 1);
        c.resize(l), NTT(c, l, 1);
        b.resize(l), NTT(b, l, 1);

        for (int re i = 0; i < l; ++i)
            b[i] = mul(b[i], dec(2, mul(c[i], b[i])));

        NTT(b, l, -1);
        b.resize(l >> 1);
    }

    b.resize(lim);
    return b;
}
inline Poly Inv(cs Poly &a) { return Inv(a, a.size()); }

inline Poly Ln(Poly a, int lim) {
    a = Integ(Deriv(a) * Inv(a, lim));
    a.resize(lim);
    return a;
}
inline Poly Ln(cs Poly &a) { return Ln(a, a.size()); }

inline Poly Exp(cs Poly &a, int lim) {
    Poly c, b(1, 1);
    int n = a.size();

    for (int re i = 2; (i >> 1) < lim; i <<= 1) {
        c = Ln(b, i);

        for (int re j = 0; j < i; ++j) c[j] = dec(j < n ? a[j] : 0, c[j]);

        c[0] = add(c[0], 1);
        b = b * c;
        b.resize(i);
    }

    b.resize(lim);
    return b;
}
inline Poly Exp(cs Poly &a) { return Exp(a, a.size()); }

cs int w4 = quickpow(3, (mod - 1) / 4);
inline Poly Cos(cs Poly &a, int lim) {
    Poly c = a;
    c.resize(lim);
    c = (Exp(c * w4) + Exp(c * (mod - w4))) * inv2;
    return c;
}
inline Poly Cos(cs Poly &a) { return Cos(a, a.size()); }

inline Poly Sin(cs Poly &a, int lim) {
    Poly c = a;
    c.resize(lim);
    c = (Exp(c * w4) - Exp(c * (mod - w4))) * mul(inv2, quickpow(w4, mod - 2));
    return c;
}
inline Poly Sin(cs Poly &a) { return Sin(a, a.size()); }

inline Poly Sqrt(cs Poly &a, int lim) {
    Poly c, d, b(1, 1);

    for (int re l = 4; (l >> 2) < lim; l <<= 1) {
        init_rev(l);
        c = a, c.resize(l >> 1);
        d = Inv(b, l >> 1);
        c.resize(l), NTT(c, l, 1);
        d.resize(l), NTT(d, l, 1);

        for (int re j = 0; j < l; ++j) c[j] = mul(c[j], d[j]);

        NTT(c, l, -1);
        b.resize(l >> 1);

        for (int re j = 0; j < (l >> 1); ++j) b[j] = mul(add(c[j], b[j]), inv2);
    }

    b.resize(lim);
    return b;
}
inline Poly Sqrt(cs Poly &a) { return Sqrt(a, a.size()); }

inline Poly Ksm(Poly a, int k, int lim) {
    a = Exp(Ln(a) * k);
    a.resize(lim);
    return a;
}
inline Poly Ksm(cs Poly &a, int k) { return Ksm(a, k, a.size()); }

inline Poly operator/(Poly a, Poly b) {
    int re len = 1, deg = a.size() - b.size() + 1;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    while (len <= deg) len <<= 1;

    b = Inv(b, len);
    b.resize(deg);
    a = a * b;
    a.resize(deg);
    reverse(a.begin(), a.end());
    return a;
}

inline Poly operator%(cs Poly &a, cs Poly &b) {
    Poly c = a - (a / b) * b;
    c.resize(b.size() - 1);
    return c;
}

inline void init_inv() {
    inv[0] = inv[1] = 1;

    for (int re i = 2; i < N; ++i) inv[i] = mul(inv[mod % i], mod - mod / i);
}
Poly A, B, C, D;
int n, m;
signed main() {
    init_inv();
    cin >> n;

    for (int i = 0; i <= n; i++) A.push_back(0);

    for (int i = 1; i <= n; i++)
        for (int j = 1; i * j <= n; j++) A[i * j] = (A[i * j] + inv[i]) % mod;

    B = Exp(A);
    std::cout << B[n];
    return 0;
}