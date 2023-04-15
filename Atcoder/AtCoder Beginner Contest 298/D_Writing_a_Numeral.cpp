#include <bits/stdc++.h>

using i64 = std::int64_t;

constexpr int P = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    i64 cur = 1;

    std::deque<int> Q;
    Q.push_back(1);

    std::vector<i64> p10(1E6 + 10, 1);
    for (int i = 1; i < p10.size(); i++) p10[i] = p10[i - 1] * 10 % P;

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int x;
            std::cin >> x;
            cur = cur * 10 % P + x;
            Q.push_back(x);
        }
        if (op == 2) {
            auto fst = Q.front();
            Q.pop_front();
            cur = ((cur - p10[Q.size()] * fst % P) % P + P) % P;
        }
        if (op == 3) {
            std::cout << cur << '\n';
        }
    }
    return 0;
}