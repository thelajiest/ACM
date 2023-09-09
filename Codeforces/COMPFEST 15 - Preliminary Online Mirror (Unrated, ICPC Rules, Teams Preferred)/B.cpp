#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n;
    std::vector<int> a(n);

    for (auto& v : a) std::cin >> v;
    std::vector<int> cnt(*std::max_element(begin(a), end(a)) + 1);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cnt[a[i]] = x;
    }
    std::cin >> m;
    std::vector<int> b(m);
    for (auto& v : b) std::cin >> v;

    for (int i = 0; i < m; i++) {
        int x;
        std::cin >> x;
        cnt[b[i]] -= x;
    }

    i64 t = 0;
    for (int i = 0; i < (int)cnt.size(); i++) {
        if (cnt[i] > 0) t++;
        if (cnt[i] < 0) {
            std::cout << 0 << std::endl;
            return 0;
        }
    }

    int ans = 1;
    while (t--) ans = 1LL * ans * 2 % 998244353;
    std::cout << ans << std::endl;

    return 0;
}