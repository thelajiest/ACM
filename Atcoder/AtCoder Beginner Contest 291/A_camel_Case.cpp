#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.size(); i++) {
        auto c = s[i];
        if ('A' <= c && c <= 'Z') {
            std::cout << i + 1 << std::endl;
            return 0;
        }
    }
    return 0;
}