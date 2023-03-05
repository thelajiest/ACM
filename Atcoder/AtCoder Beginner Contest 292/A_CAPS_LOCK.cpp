#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    for (auto c : s) {
        std::cout << char(c - 'a' + 'A');
    }

    std::cout << '\n';

    return 0;
}