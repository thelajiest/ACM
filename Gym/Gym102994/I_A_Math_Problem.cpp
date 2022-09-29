#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <class T>
T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
template <int mod>
struct ModInt {
    i64 x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt<mod>(t);
        return (is);
    }

    int get() const { return x; }

    static constexpr int get_mod() { return mod; }
};

constexpr int mod = 1e9 + 7;
using Z = ModInt<mod>;
i64 powmod(i64 a, i64 b) {
    i64 res = 1;
    a %= mod;
    assert(b >= 0);
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
namespace linear_seq {
const int N = 10010;
i64 res[N], base[N], _c[N], _md[N];
vector<i64> Md;
void mul(i64 *a, i64 *b, int k) {
    for (int i = 0; i < k + k; i++) _c[i] = 0;
    for (int i = 0; i < k; i++)
        if (a[i])
            for (int j = 0; j < k; j++)
                _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
    for (i64 i = k + k - 1; i >= k; i--)
        if (_c[i])
            for (int j = 0; j < Md.size(); j++)
                _c[i - k + Md[j]] =
                    (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
    for (int i = 0; i < k; i++) a[i] = _c[i];
}
int solve(i64 n, vector<i64> a, vector<i64> b) {
    i64 ans = 0, pnt = 0;
    i64 k = a.size();
    assert(a.size() == b.size());
    for (int i = 0; i < k; i++) _md[k - 1 - i] = -a[i];
    _md[k] = 1;
    Md.clear();
    for (int i = 0; i < k; i++)
        if (_md[i] != 0) Md.push_back(i);
    for (int i = 0; i < k; i++) res[i] = base[i] = 0;
    res[0] = 1;
    while ((1ll << pnt) <= n) pnt++;
    for (i64 p = pnt; p >= 0; p--) {
        mul(res, res, k);
        if ((n >> p) & 1) {
            for (i64 i = k - 1; i >= 0; i--) res[i + 1] = res[i];
            res[0] = 0;
            for (int j = 0; j < Md.size(); j++)
                res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
        }
    }
    for (int i = 0; i < k; i++) ans = (ans + res[i] * b[i]) % mod;
    if (ans < 0) ans += mod;
    return ans;
}
vector<i64> BM(vector<i64> s) {
    vector<i64> C(1, 1), B(1, 1);
    int L = 0, m = 1, b = 1;
    for (int n = 0; n < s.size(); n++) {
        i64 d = 0;
        for (int i = 0; i < L + 1; i++) d = (d + (i64)C[i] * s[n - i]) % mod;
        if (d == 0)
            ++m;
        else if (2 * L <= n) {
            vector<i64> T = C;
            i64 c = mod - d * powmod(b, mod - 2) % mod;
            while (C.size() < B.size() + m) C.push_back(0);
            for (int i = 0; i < B.size(); i++)
                C[i + m] = (C[i + m] + c * B[i]) % mod;
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        } else {
            i64 c = mod - d * powmod(b, mod - 2) % mod;
            while (C.size() < B.size() + m) C.push_back(0);
            for (int i = 0; i < B.size(); i++)
                C[i + m] = (C[i + m] + c * B[i]) % mod;
            ++m;
        }
    }
    return C;
}
int gao(vector<i64> a, i64 n) {
    vector<i64> c = BM(a);
    c.erase(c.begin());
    for (int i = 0; i < c.size(); i++) c[i] = (mod - c[i]) % mod;
    return solve(n, c, vector<i64>(a.begin(), a.begin() + c.size()));
}
};  // namespace linear_seq
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        i64 n, m;
        cin >> n >> m;
        if (m == 2) {
            cout << 2 << '\n';
        }
        if (m == 3) {
            Z ans = (power(Z(2), n) - 2) * Z(6);
            cout << ans << '\n';
        }
        if (m == 4) {
            Z ans = power(Z(2), n - 1) + Z(2) + power(Z(3), n) -
                    Z(3) * power(Z(2), n);
            cout << ans * Z(24) << '\n';
        }
        if (m == 5) {
            Z ans =
                power(Z(4), n) - power(Z(3), n + 1) + Z(3) * power(Z(2), n) - 1;
            cout << ans * Z(120) << '\n';
        }

        if (m == 6) {
            // 2 - 2^(2+n) - 7*2^(2*n-1) + 5*3^n + 5^n

            // Z ans = Z(2) - power(Z(2), 2 + n) - Z(7) * power(Z(2), 2 * n - 1)
            // +
            //         Z(5) * power(Z(3), n) + power(Z(5), n);

            // cerr << ans * Z(720) << '\n';
            cout << linear_seq::gao(
                        vector<i64>({0, 0, 4320, 51840, 453600, 3369600,
                                     22468320, 138983040, 815032800, 598467172,
                                     218436145, 404057295}),
                        n - 1)
                 << '\n';
        }
    }
}