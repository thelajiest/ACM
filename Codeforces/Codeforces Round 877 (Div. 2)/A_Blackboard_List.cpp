#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    auto max = *(std::max_element(begin(a), end(a)));
    auto min = *(std::min_element(begin(a), end(a)));

    if (min >= 0) {
        std::cout << max << '\n';
    } else {
        std::cout << min << '\n';
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