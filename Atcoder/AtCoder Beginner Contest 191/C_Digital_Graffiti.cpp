#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int h, w;
    std::cin >> h >> w;

    std::vector<std::vector<char>> mp(h, std::vector<char>(w));

    for (int i = 0; i < h; i++) {
        std::string s;
        std::cin >> s;
        mp[i] = {s.begin(), s.end()};
    }

    int ans = 0;
    for (int i = 0; i < h - 1; i++) {
        for (int j = 0; j < w - 1; j++) {
            int cur = 0;
            if (mp[i][j] == '#') cur++;
            if (mp[i][j + 1] == '#') cur++;
            if (mp[i + 1][j] == '#') cur++;
            if (mp[i + 1][j + 1] == '#') cur++;
            if (cur == 3 || cur == 1) ans++;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}