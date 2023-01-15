#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 ans = 0;

    std::string s;

    std::cin >> s;

    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        ans = ans * 26 + (s[i] - 'A' + 1);
    }

    std::cout << ans << std::endl;
    return 0;
}