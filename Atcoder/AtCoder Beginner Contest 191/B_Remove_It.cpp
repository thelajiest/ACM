#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x;
    std::cin >> n >> x;

    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        int cur;
        std::cin >> cur;
        if (cur != x) ans.push_back(cur);
    }

    for (auto p : ans) std::cout << p << " ";
    std::cout << std::endl;

    return 0;
}