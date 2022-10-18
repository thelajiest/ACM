#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

inline i64 binary_gcd(i64 a, i64 b) {
    if (a == 0 || b == 0) return a + b;
    char n = __builtin_ctzll(a);
    char m = __builtin_ctzll(b);
    a >>= n;
    b >>= m;
    n = std::min(n, m);
    while (a != b) {
        i64 d = a - b;
        char s = __builtin_ctzll(d);
        bool f = a > b;
        b = f ? b : a;
        a = (f ? d : -d) >> s;
    }
    return a << n;
}
template <class T>
T mul(T x, T y, T c) {
    if (is_same<int, T>::value) return 1ll * x * y % c;
    if (is_same<i64, T>::value) return __int128(x) * y % c;
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
                while (t++ % 40 || binary_gcd(prd, n) == 1) {
                    if (x == y) x = myrand(2, n - 1), y = f(x);
                    T tmp = mul(prd, (x - y) > 0 ? (x - y) : (y - x), n);
                    if (tmp) prd = tmp;
                    x = f(x), y = f(f(y));
                }
                return binary_gcd(prd, n);
            }(x);
            solve(d);
            solve(x / d);
        }
    };

    solve(n);

    return res;
}

template <class T>
vector<T> OsakDivisorsFast(T x) {
    auto fac = factorization<i64>(x);
    sort(fac.begin(), fac.end());
    vector<pair<T, int>> lt;
    for (int i = 0, j; i < int(fac.size()); i = j) {
        j = i;
        while (fac[j] == fac[i] && j < int(fac.size())) j++;
        lt.emplace_back(fac[i], j - i);
    }
    vector<T> div;
    auto dfs = [&](auto rec, int i, T c) {
        if (i == int(lt.size())) {
            div.push_back(c);
            return;
        }
        for (int j = 0; j <= lt[i].second; j++) {
            rec(rec, i + 1, c);
            c *= lt[i].first;
        }
    };
    dfs(dfs, 0, 1);
    return div;
}
vector<int> prime_sieve(int N) {
    vector<bool> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}
template <class T>
vector<T> OsakDivisors(T x) {
    auto primes = prime_sieve(sqrt(x) + 10);

    vector<pair<T, int>> lt;
    for (auto p : primes) {
        if (1LL * p * p > x) break;
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        lt.emplace_back(p, cnt);
    }
    if (x > 1) lt.emplace_back(x, 1);
    vector<T> div;
    auto dfs = [&](auto rec, int i, T c) {
        if (i == int(lt.size())) {
            div.push_back(c);
            return;
        }
        for (int j = 0; j <= lt[i].second; j++) {
            rec(rec, i + 1, c);
            c *= lt[i].first;
        }
    };
    dfs(dfs, 0, 1);
    return div;
}
void solve() {
    int a, b, c, d;

    cin >> a >> b >> c >> d;

    auto div1 = OsakDivisorsFast<int>(a);
    auto div2 = OsakDivisorsFast<int>(b);
    for (auto it1 : div1) {
        for (auto it2 : div2) {
            i64 it = 1LL * it1 * it2;
            if (a / it != c / it) {
                i64 tmp = 1LL * a * b / it;
                if (b / tmp != d / tmp) {
                    cout << (a / it + 1) * it << ' ' << (b / tmp + 1) * tmp
                         << '\n';
                    return;
                }
            }
        }
    }
    cout << "-1 -1\n";

    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
