#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    for (int i = 0; i < 16; i++) {
        if ((i & 1) && s[i] == '1') {
            std::cout << "No";
            return 0;
        }
    }

    std::cout << "Yes";

    return 0;
}