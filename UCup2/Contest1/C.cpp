#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr int B = 256;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::tuple<int, int, int>> op(n);
    for (int i = 0; i < n; i++) {
        std::string _op;
        std::cin >> _op;
        int t = 0;
        if (_op == "add") t = 0;
        if (_op == "beq") t = 1;
        if (_op == "bne") t = 2;
        if (_op == "blt") t = 3;
        if (_op == "bgt") t = 4;
        if (t > 0) {
            int a, b;
            std::cin >> a >> b;
            b--;
            op[i] = {t, a, b};
        } else {
            int a;
            std::cin >> a;
            op[i] = {t, a, 0};
        }
    }

    std::queue<std::pair<int, int>> Q;
    std::vector vis(n + 1, std::vector(B, 0));

    Q.push({0, 0});
    vis[0][0] = 1;
    while (!Q.empty()) {
        auto [x, r] = Q.front();
        // std::cerr << x << " " << r << std::endl;
        Q.pop();
        if (x == n) break;

        auto [_op, v, k] = op[x];
        int y = 0, yr = 0;
        if (_op == 0) {
            y = x + 1;
            yr = (r + v) % B;
        }
        if (_op == 1) {
            if (r == v)
                y = k;
            else
                y = x + 1;
            yr = r;
        }
        if (_op == 2) {
            if (r != v)
                y = k;
            else
                y = x + 1;
            yr = r;
        }
        if (_op == 3) {
            if (r < v)
                y = k;
            else
                y = x + 1;
            yr = r;
        }
        if (_op == 4) {
            if (r > v)
                y = k;
            else
                y = x + 1;
            yr = r;
        }
        if (!vis[y][yr]) {
            Q.push({y, yr});
            vis[y][yr] = 1;
        }
    }

    for (int i = 0; i < B; i++) {
        if (vis[n][i]) {
            std::cout << "Yes\n";
            return;
        }
    }
    std::cout << "No\n";

    std::cerr << std::endl;
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}