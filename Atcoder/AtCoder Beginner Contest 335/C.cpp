#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::deque<std::pair<int, int>> Q;

    int N;
    std::cin >> N;

    for (int i = 1; i <= N; i++) {
        Q.push_back({i, 0});
    }

    int q;
    std::cin >> q;

    while (q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            char c;
            std::cin >> c;

            auto [x, y] = Q.front();
            if (c == 'U') Q.push_front({x, y + 1});
            if (c == 'D') Q.push_front({x, y - 1});
            if (c == 'L') Q.push_front({x - 1, y});
            if (c == 'R') Q.push_front({x + 1, y});

            Q.pop_back();
        } else {
            int x;
            std::cin >> x;
            x--;

            auto [dx, dy] = Q[x];

            std::cout << dx << " " << dy << '\n';
        }
    }

    return 0;
}