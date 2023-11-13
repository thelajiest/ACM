#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<int, int>> a;

    int N;
    std::cin >> N;
    std::vector<std::string> s(N);
    for (int i = 0; i < N; i++) {
        std::cin >> s[i];
    }

    for (int i = 0; i < N; i++) {
        int sum = std::count(std::begin(s[i]), std::end(s[i]), 'o');
        a.push_back({-sum, i});
    }

    std::sort(begin(a), end(a));

    for (auto [sum, i] : a) {
        std::cout << i + 1 << " ";
    }

    return 0;
}
