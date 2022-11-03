#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <typename T>
void walsh_hadamard_transform(vector<T>& f, bool inverse = false) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                T x = f[j], y = f[j | i];
                f[j] = x + y, f[j | i] = x - y;
            }
        }
    }
    if (inverse) {
        if constexpr (is_integral<T>::value) {
            for (auto& x : f) x /= n;
        } else {
            T invn = T(1) / T(f.size());
            for (auto& x : f) x *= invn;
        }
    }
}
template <typename T>
vector<T> xor_convolution(vector<T> a, vector<T> b) {
    walsh_hadamard_transform(a);
    walsh_hadamard_transform(b);
    for (int i = 0; i < (int)a.size(); i++) a[i] *= b[i];
    walsh_hadamard_transform(a, true);
    return a;
}

template <typename T>
void subset_zeta_transform(vector<T>& f) {
    int n = f.size();
    assert((n & (n - 1)) == 0);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                f[j | i] += f[j];
            }
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n, m, k;
    cin >> n >> m >> k;
    vector<i64> a(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'A') a[i] += (1LL << j);
        }
    }

    vector<i64> cnt(1 << m);

    for (int i = 0; i < n; i++) cnt[a[i]]++;
    auto xorConv = xor_convolution(cnt, cnt);

    for (auto& it : xorConv) it /= 2;
    subset_zeta_transform(xorConv);
    auto f = xorConv;

    i64 ans = 0;
    for (int i = 0; i < (1 << m); i++) {
        if (1LL * n * (n) / 2 - f[i] >= k) ans++;
    }

    cout << ans << endl;

    return 0;
}