#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int H, W, N;
    std::string T;

    std::cin >> H >> W >> N >> T;

    std::vector<std::vector<char>> adx(H, std::vector<char>(W));
    for (int i = 0; i < H; i++) {
        std::string in;
        std::cin >> in;
        adx[i] = {std::begin(in), std::end(in)};
    }

    auto check = [&](int x, int y) -> bool {
        int curx = x, cury = y;
        for (int i = 0; i < N; i++) {
            if (curx >= H || curx < 0) return false;
            if (cury >= W || cury < 0) return false;
            if (adx[curx][cury] == '#') return false;
            if (T[i] == 'L') cury -= 1;
            if (T[i] == 'R') cury += 1;
            if (T[i] == 'U') curx -= 1;
            if (T[i] == 'D') curx += 1;
        }

        if (adx[curx][cury] == '#') return false;
        return true;
    };

    int cnt = 0;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cnt += check(i, j);
        }
    }

    std::cout << cnt << std::endl;
    return 0;
}