#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int mod = 998244353;
constexpr int N = 2E7;
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
using Z = mint<mod>;
std::array<Z, N + 1> fac, ifac;

template <class T>
T Comb(int n, int m) {
    assert(n <= N && m <= N);
    if (n < 0 || m < 0 || n < m) return 0;

    return fac[n] * ifac[m] * ifac[n - m];
}

template <class T>
T countGrid(pair<int, int> A, pair<int, int> B, int ta, int tb) {
    /*
        from A to B without go outside y=x+ta,y=x-tb
    */
    auto [x, y] = A;
    auto [a, b] = B;
    if (a + ta < b || a - tb > b) return 0;
    if (x + ta < y || x - tb > y) return 0;
    int n = a - x;
    int m = b - y;

    return Comb<Z>(n + m, m) -
           Comb<Z>(n + m - (x + ta - y), m - (x + ta - y) - 1) -
           Comb<Z>(n - (y - (x - tb)) + m, n - (y - (x - tb)) - 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * Z(i);
    ifac[N] = fac[N].inverse();
    for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i;

    int n, m;

    cin >> n >> m;

    Z ans = 0;
    for (int x = 0; x <= n; x++) {
        int y = n - x;
        ans += countGrid<Z>(pair<int, int>{0, 0}, pair<int, int>{x, y}, 0,
                            (m + 1) / 2);
    }

    cout << ans << '\n';

    return 0;
}