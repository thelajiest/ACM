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

constexpr int mod = 998244353;
using Z = mint<mod>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    if (m == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    vector<Z> fac(n + 1);
    fac[0] = Z(1);
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * Z(i);
    Z ans = 1;
    vector<int> vis(n + 1);
    int g = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int now = i;
            vis[now] = 1;
            int cnt = 1;
            while (p[now] != i) {
                now = p[now];
                vis[now] = 1;
                cnt++;
            }
            g++;
        }
    }
    cout << Z(power<Z>(m, n) - power<Z>(m, g)) / Z(2);
    return 0;
}