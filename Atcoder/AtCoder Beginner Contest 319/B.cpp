#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::string s;

    for (int i = 0; i <= n; i++) {
        s += "-";
        for (int j = 1; j <= 9; j++) {
            if (n % j == 0 && i % (n / j) == 0) {
                s[i] = j + '0';
                break;
            }
        }
    }

    std::cout << s << std::endl;

    return 0;
}