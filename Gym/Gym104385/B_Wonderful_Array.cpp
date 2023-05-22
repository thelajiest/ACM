#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 k;
    std::cin >> k;

    std::vector<i64> a(k);
    for (int i = 0; i < k; i++) std::cin >> a[i];

    i64 n, m, x;
    std::cin >> n >> m >> x;

    for (int i = 0; i < k; i++) a[i] %= m;
    i64 sum = std::accumulate(a.begin(), a.end(), 0LL);

    i64 last = x + 1LL * (n - 1) / k * sum;

    for (int i = 0; i <= (n - 1) % k; i++) last += a[i];

    last /= m;

    i64 ans = 0;
    for (auto p : a)
        if (p % m == 0) ans++;
    ans += n - last;

    std::cout << ans;

    return 0;
}