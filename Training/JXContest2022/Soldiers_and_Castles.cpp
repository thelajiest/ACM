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
constexpr int N = 6E5;
using Z = mint<mod>;

template <typename T>
std::pair<int, T> GaussElimination(vector<vector<T>> &a, int pivot_end = -1,
                                   bool diagonalize = false) {
    int H = a.size(), W = a[0].size();
    int rank = 0, je = pivot_end;
    if (je == -1) je = W;
    T det = 1;
    for (int j = 0; j < je; j++) {
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
        if (rank != idx) {
            det = -det;
            swap(a[rank], a[idx]);
        }
        det *= a[rank][j];
        if (diagonalize && a[rank][j] != T(1)) {
            T coeff = a[rank][j].inverse();
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
    return make_pair(rank, det);
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Z> fac(N), invf(N);

    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * Z(i);
    for (int i = 0; i < N; i++) invf[i] = Z(1) / fac[i];

    auto Comb = [&](int n, int m) -> Z {
        if (n < 0 || m < 0 || n < m) return Z(0);
        return fac[n] * invf[n - m] * invf[m];
    };

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> sol, cas;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        sol.emplace_back(x, y);
        cin >> x >> y;
        cas.emplace_back(x, y);
    }
    sort(sol.begin(), sol.end());
    sort(cas.begin(), cas.end());

    sol.resize(unique(sol.begin(), sol.end()) - sol.begin());
    cas.resize(unique(cas.begin(), cas.end()) - cas.begin());
    if (sol.size() != n || cas.size() != n) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<Z>> LGV(n, vector<Z>(n));

    auto GetPath = [&](pair<int, int> A, pair<int, int> B) {
        auto [x, y] = A;
        auto [a, b] = B;
        int n = a - x;
        int m = b - y;

        return Comb(n + m, m) - Comb(n + m, m - (x + k - y) - 1) -
               Comb(n + m, n - (y - (x - k)) - 1);
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            LGV[i][j] = GetPath(sol[i], cas[j]);
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) cerr << LGV[i][j] << " ";
    //     cerr << endl;
    // }

    auto [rk, det] = GaussElimination(LGV);
    if (rk == n)
        cout << det << endl;
    else
        cout << 0 << endl;

    return 0;
}