#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

template <class T>
T mul(T x, T y, T c) {
    if (is_same<int, T>::value) return 1ll * x * y % c;
    if (is_same<i64, T>::value) return __int128(x) * y % c;
    if (is_same<u64, T>::value) return (unsigned __int128)(x)*y % c;

    return x * y % c;
}
template <class T>
bool miller(T n) {
    if (n == 2) return 1;

    for (auto p : {2, 3, 5, 7, 11, 13})
        if ([&](T n, int a) -> bool {
                if (n == a) return 1;
                if (n % 2 == 0) return 0;
                auto mpow = [&](T a, T k, T mod) {
                    T res = 1;
                    for (; k; k /= 2, a = mul<T>(a, a, mod))
                        if (k & 1) res = mul<T>(res, a, mod);
                    return res;
                };
                T d = (n - 1) >> __builtin_ctzll(n - 1);
                T r = mpow(a, d, n);

                while (d < n - 1 && r != 1 && r != n - 1)
                    d <<= 1, r = mul<T>(r, r, n);
                return r == n - 1 || d & 1;
            }(n, p) == 0)
            return 0;

    return 1;
}
template <class T>
vector<T> factorization(T n) {
    static mt19937_64 rng(114514);
    auto myrand = [&](i64 a, i64 b) -> i64 {
        return uniform_int_distribution<i64>(a, b)(rng);
    };

    vector<T> res;

    function<void(T)> solve = [&](T x) {
        if (x == 1) return;
        if (miller(x))
            res.push_back(x);
        else {
            T d = [&](T n) {
                auto f = [&](T x) -> T { return (mul<T>(x, x, n) + 1) % n; };
                T x = 0, y = 0, t = 30, prd = 2;
                while (t++ % 40 || std::gcd(prd, n) == 1) {
                    if (x == y) x = myrand(2, n - 1), y = f(x);
                    T tmp = mul(prd, (x - y) > 0 ? (x - y) : (y - x), n);
                    if (tmp) prd = tmp;
                    x = f(x), y = f(f(y));
                }
                return std::gcd(prd, n);
            }(x);
            solve(d);
            solve(x / d);
        }
    };

    solve(n);

    return res;
}
void solve() {
    u64 n;
    std::cin >> n;

    auto fac = factorization<u64>(n);

    sort(begin(fac), end(fac));

    if (fac[0] == fac[1]) {
        cout << fac[0] << ' ' << fac[2] << '\n';
    } else {
        cout << fac[1] << ' ' << fac[0] << '\n';
    }

    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;

    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}