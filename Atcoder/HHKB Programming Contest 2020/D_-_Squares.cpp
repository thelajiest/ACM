#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

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
constexpr int mod = 1E9 + 7;
using Z = mint<mod>;
void solve() {
    i64 N, a, b;
    cin >> N >> a >> b;
    Z ans = Z(N - a + 1) * Z(N - a + 1) * Z(N - b + 1) * Z(N - b + 1);
    auto f0 = [&](int l, int r) { return Z(r - l + 1); };
    auto f1 = [&](int l, int r) { return Z(r - l + 1) * Z(l + r) / Z(2); };
    auto f2 = [&](int l, int r) {
        auto gao = [&](int x) -> Z {
            return Z(x) * Z(x + 1) * Z(2 * x + 1) / Z(6);
        };
        if (l >= 1) return gao(r) - gao(l - 1);
        return gao(r);
    };
    Z ans2 = 0;
    ans2 += Z(N + 1) * Z(N + 1) * f0(max(a, b) + 1, min(a + b - 1, N));
    ans2 += f2(max(a, b) + 1, min(a + b - 1, N));
    ans2 -= f1(max(a, b) + 1, min(a + b - 1, N)) * Z(2 * (N + 1));
    ans2 *= Z(2);
    if (b < a) swap(a, b);
    ans2 += Z(2) * Z(N - b + 1) * Z(N - b + 1) * Z(b - a + 1) * Z(b + a - 1);
    cout << ans - ans2 << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}