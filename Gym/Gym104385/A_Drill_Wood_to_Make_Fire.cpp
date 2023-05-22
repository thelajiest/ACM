#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int N, S, V;
    std::cin >> N >> S >> V;

    std::cout << (S * V >= N) << '\n';

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