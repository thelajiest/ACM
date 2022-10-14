#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
template <typename T>
T inv(T a, T p) {
    T b = p, x = 1, y = 0;
    while (a) {
        T q = b / a;
        swap(a, b %= a);
        swap(x, y -= q * x);
    }
    assert(b == 1);
    return y < 0 ? y + p : y;
}

int64_t mod_log(int64_t a, int64_t b, int64_t p) {
    if ((a %= p) < 0) a += p;
    if ((b %= p) < 0) b += p;
    int64_t f, g, r = 1 % p;
    for (f = 0; (g = gcd(a, p)) > 1; ++f) {
        if (b % g) return (r == b) ? f : -1;
        b /= g;
        p /= g;
        (r *= (a / g)) %= p;
    }
    if (p == 1) return f;
    int64_t ir = inv(r, p);
    (b *= ir) %= p;
    int64_t k = 0, ak = 1;
    unordered_map<i64, i64> baby;
    for (; k * k < p; ++k) {
        if (baby.find(ak) == baby.end()) baby[ak] = k;
        (ak *= a) %= p;
    }
    int64_t iak = inv(ak, p);
    for (int64_t i = 0; i < k; ++i) {
        if (baby.find(b) != baby.end()) return f + i * k + baby[b];
        (b *= iak) %= p;
    }
    return -1;
}
void solve() {
    i64 k;
    cin >> k;
    if (k % 2 == 0) k /= 2;
    k *= 9;
    if (gcd(10, k) != 1) {
        cout << -1 << endl;
        return;
    }
    i64 b = (9 * k * inv(2LL, k) % k + 1) * inv(10LL, k) % k;
    auto ans = mod_log(10, b, k);
    if (ans == -1) {
        cout << -1 << endl;
        return;
    }
    cout << mod_log(10, b, k) + 1 << endl;
    return;
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