#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> cnt(n, 1);

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        x--;
        if (cnt[i]) cnt[x] = 0;
    }

    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (cnt[i]) ans.push_back(i + 1);
    }

    std::cout << ans.size() << std::endl;
    for (auto p : ans) {
        std::cout << p << " \n"[p == ans.back()];
    }

    return 0;
}