#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    for (auto& c : s) {
        std::cout << c << c;
    }

    std::cout << std::endl;

    return 0;
}