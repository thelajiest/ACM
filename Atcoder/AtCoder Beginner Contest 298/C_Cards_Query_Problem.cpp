#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::multiset<int>> a(n + 1);
    std::vector<std::set<int>> b(2E5 + 1);

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int i, x;
            std::cin >> x >> i;
            a[i].insert(x);
            b[x].insert(i);
        }
        if (op == 2) {
            int x;
            std::cin >> x;
            for (auto p : a[x]) std::cout << p << " ";
            std::cout << '\n';
        }
        if (op == 3) {
            int x;
            std::cin >> x;
            for (auto p : b[x]) std::cout << p << " ";
            std::cout << '\n';
        }
    }
    return 0;
}