#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, ans;
    std::cin >> s;

    for (auto c : s) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') continue;
        ans += c;
    }

    std::cout << ans << std::endl;

    return 0;
}