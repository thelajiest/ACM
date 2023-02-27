#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::map<std::pair<int, int>, int> mp;

    mp[{0, 0}] = 1;
    std::string s;
    std::cin >> s;

    std::pair<int, int> cur = {0, 0};
    bool flag = false;

    for (auto c : s) {
        auto& [x, y] = cur;
        if (c == 'R') x++;
        if (c == 'L') x--;
        if (c == 'U') y++;
        if (c == 'D') y--;
        if (mp[cur]) flag = true;
        mp[cur]++;
    }

    if (flag)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}