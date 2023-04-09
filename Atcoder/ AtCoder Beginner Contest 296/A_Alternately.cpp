#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    bool ok = true;

    for (int i = 0; i + 1 < n; i++) {
        if (s[i] == s[i + 1]) ok = false;
    }

    if (ok)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}