#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<char>> mp(8);
    for (int i = 0; i < 8; i++) {
        std::string in;
        std::cin >> in;
        mp[i] = {in.begin(), in.end()};
    }

    int retx = -1, rety = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (mp[i][j] == '*') retx = 8 - i - 1, rety = j;
        }
    }

    std::cout << char(rety + 'a') << retx + 1;

    return 0;
}