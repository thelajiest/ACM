#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::set<int> neverCall;
    for (int i = 1; i <= n; i++) neverCall.insert(i);
    std::set<int> calledNotCome;

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            if (neverCall.size() > 0) {
                auto p = neverCall.begin();
                calledNotCome.insert(*p);
                neverCall.erase(p);
            }
        }
        if (op == 2) {
            int x;
            std::cin >> x;
            auto it = calledNotCome.find(x);
            calledNotCome.erase(it);
        }
        if (op == 3) {
            auto it = calledNotCome.begin();
            std::cout << *it << std::endl;
        }
    }
    return 0;
}