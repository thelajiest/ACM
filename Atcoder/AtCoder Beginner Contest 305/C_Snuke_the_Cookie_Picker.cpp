#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    std::cin >> H >> W;
    std::vector<std::vector<char>> mp(H);
    for (int i = 0; i < H; i++) {
        std::string s;
        std::cin >> s;
        mp[i] = {begin(s), end(s)};
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (mp[i][j] == '#') continue;
            int d = 0;
            if (i > 0 && mp[i - 1][j] == '#') d++;
            if (i < H - 1 && mp[i + 1][j] == '#') d++;
            if (j > 0 && mp[i][j - 1] == '#') d++;
            if (j < W - 1 && mp[i][j + 1] == '#') d++;
            if (d > 1) {
                std::cout << i + 1 << " " << j + 1 << std::endl;
            }
        }
    }
    return 0;
}