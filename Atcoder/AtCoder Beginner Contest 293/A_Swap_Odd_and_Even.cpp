#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    for (int i = 0; i < s.size() / 2; i++) {
        std::swap(s[2 * i], s[2 * i + 1]);
    }

    std::cout << s << std::endl;

    return 0;
}