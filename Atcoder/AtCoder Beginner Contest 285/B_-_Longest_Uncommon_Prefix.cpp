#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    s = " " + s;
    for (int j = 1; j <= n - 1; j++) {
        int l = 0, r = n - j;
        while (l < r) {
            int m = (l + r + 1) / 2;
            auto check = [&](int x) -> bool {
                for (int i = 1; i <= x; i++) {
                    if (s[i] == s[i + j]) return false;
                }
                return true;
            };
            if (check(m))
                l = m;
            else
                r = m - 1;
        }

        std::cout << l << '\n';
    }
    return 0;
}