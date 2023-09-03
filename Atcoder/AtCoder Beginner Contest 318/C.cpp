#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, d, p;
    std::cin >> n >> d >> p;
    std::vector<i64> f(n);
    for (int i = 0; i < n; i++) std::cin >> f[i];
    std::sort(begin(f), end(f));
    i64 ans = 1E18;
    std::vector<i64> sum(n, 0);
    sum[0] = f[0];
    for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + f[i];

    for (int i = 0; i * d < n; i++) {
        ans = std::min<i64>(ans, 1LL * i * p + sum[n - d * i - 1]);
    }

    ans = std::min<i64>(ans, 1LL * ((n + d - 1) / d) * p);
    std::cout << ans << std::endl;
    return 0;
}