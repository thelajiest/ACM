#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n, k;
    std::cin >> n >> k;

    constexpr auto get = [](int n) -> int { return n * (n + 1) / 2; };

    int p = 0;
    while (get(p + 1) <= k) p++;
    int res = k - get(p);

    if (res == 0) {
        for (int i = 0; i < p; i++) std::cout << 1 << " ";
        for (int i = p; i < n; i++) std::cout << -1000 << " ";
        std::cout << '\n';

        return;
    }

    std::vector<int> ret(n, -1000);
    for (int i = 0; i < p; i++) {
        if (i == res - 1)
            ret[i] = 2;
        else
            ret[i] = 1;
    }
    ret[p] = res - 1 - p;

    for (int i = 0; i < n; i++) std::cout << ret[i] << " \n"[i == n - 1];

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