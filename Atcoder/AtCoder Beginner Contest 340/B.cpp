#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Q;
    std::cin >> Q;

    std::vector<int> a;
    while (Q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int x;
            std::cin >> x;
            a.push_back(x);
        } else {
            int k;
            std::cin >> k;
            int size = std::size(a);

            std::cout << a[size - k] << '\n';
        }
    }

    return 0;
}