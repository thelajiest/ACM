#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;

    std::multiset<int> a;
    std::multiset<int> b;
    std::cin >> q;

    int eq = 0;
    while (q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int x;
            std::cin >> x;

            auto pos = a.insert(x);

            if (pos != a.begin()) {
                auto prev = pos;
                prev--;
                b.insert((*pos) ^ (*prev));
            }
            if (std::next(pos) != a.end()) {
                auto next = pos;
                next++;
                b.insert((*pos) ^ (*next));
            }
            if (pos != a.begin() && std::next(pos) != a.end()) {
                auto prev = pos;
                prev--;
                auto next = pos;
                next++;
                auto eraseIter = b.find((*next) ^ (*prev));
                b.erase(eraseIter);
            }
        }

        if (op == 2) {
            int x;
            std::cin >> x;

            auto pos = a.find(x);

            if (pos != a.begin()) {
                auto prev = pos;
                prev--;
                auto eraseIter = b.find((*pos) ^ (*prev));
                b.erase(eraseIter);
            }
            if (std::next(pos) != a.end()) {
                auto next = pos;
                next++;
                auto eraseIter = b.find((*pos) ^ (*next));
                b.erase(eraseIter);
            }
            if (pos != a.begin() && std::next(pos) != a.end()) {
                auto prev = pos;
                prev--;
                auto next = pos;
                next++;
                b.insert((*prev) ^ (*next));
            }

            a.erase(pos);
        }

        if (op == 3) {
            std::cout << *(b.begin()) << '\n';
        }
    }
    return 0;
}