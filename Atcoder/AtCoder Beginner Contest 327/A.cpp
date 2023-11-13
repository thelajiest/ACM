#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    for (int i = 0; i + 1 < n; i++) {
        if (s[i] == 'a' and s[i + 1] == 'b' or
            s[i] == 'b' and s[i + 1] == 'a') {
            std::cout << "Yes";
            return 0;
        }
    }

    std::cout << "No";
    return 0;
}