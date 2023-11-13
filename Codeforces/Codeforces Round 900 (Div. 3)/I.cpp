#include <bits/stdc++.h>
using i64 = std::int64_t;

constexpr int P = 998244353;
const int SEED = time(0);
std::mt19937 seed(SEED);

inline int randomInt(int l, int r) {
    // return Int [l,r);
    std::uniform_int_distribution<int> RNG(l, r - 1);
    return RNG(seed);
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
using Z = mint<P>;

template <typename T>
std::pair<int, T> GaussElimination(std::vector<std::vector<T>> &a,
                                   int pivot_end = -1,
                                   bool diagonalize = false) {
    int H = a.size(), W = a[0].size(), rank = 0;
    if (pivot_end == -1) pivot_end = W;
    T det = 1;
    for (int j = 0; j < pivot_end; j++) {
        int idx = -1;
        for (int i = rank; i < H; i++) {
            if (a[i][j] != T(0)) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            det = 0;
            continue;
        }
        if (rank != idx) det = -det, std::swap(a[rank], a[idx]);
        det *= a[rank][j];
        if (diagonalize && a[rank][j] != T(1)) {
            T coeff = T(1) / a[rank][j];
            for (int k = j; k < W; k++) a[rank][k] *= coeff;
        }
        int is = diagonalize ? 0 : rank + 1;
        for (int i = is; i < H; i++) {
            if (i == rank) continue;
            if (a[i][j] != T(0)) {
                T coeff = a[i][j] / a[rank][j];
                for (int k = j; k < W; k++) a[i][k] -= a[rank][k] * coeff;
            }
        }
        rank++;
    }
    return std::make_pair(rank, det);
}

void solve(int n, int m) {
    std::vector<int> d(n), f(n);
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }
    f[0] = d[0];
    for (int i = 0; i + 1 < n; i++) f[i + 1] += f[i] + d[i + 1];

    int cnt = f.back();

    std::vector adx(1000, std::vector(1000, Z(0)));
    auto addedge = [&](int x, int y) {
        adx[x][y] = randomInt(0, P);
        adx[y][x] = -adx[x][y];
        return;
    };
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        int dx = cnt, dy = cnt + 1;

        addedge(dx, f[x] - 1);
        if (d[x] == 2) {
            addedge(dx, f[x] - 2);
        }

        addedge(dy, f[y] - 1);
        if (d[y] == 2) {
            addedge(dy, f[y] - 2);
        }
        addedge(dx, dy);
        cnt += 2;
    }

    adx.resize(cnt);
    for (auto &v : adx) v.resize(cnt);

    auto [rank, det] = GaussElimination(adx);
    if (det == 0)
        std::cout << "No\n";
    else
        std::cout << "Yes\n";

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    while (std::cin >> n >> m) {
        solve(n, m);
    }

    return 0;
}