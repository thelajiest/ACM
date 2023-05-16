#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    int win = (n + 1) / 2;

    int c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A')
            c1++;
        else
            c2++;
        if (c1 == win) {
            std::cout << "A";
            break;
        }
        if (c2 == win) {
            std::cout << "T";
            break;
        }
    }

    return 0;
}