#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') a++;
        if (s[i] == 'B') b++;
        if (s[i] == 'C') c++;
        if ((a != 0) && (b != 0) && (c != 0)) {
            std::cout << i + 1 << std::endl;
            return 0;
        }
    }
    return 0;
}