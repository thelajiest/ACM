#include <bits/stdc++.h>
using i64 = std::int64_t;

constexpr int B = 6000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::list<std::pair<std::vector<int>, std::set<int>>> l;

    std::vector<int> a;
    std::set<int> s;
    for (int i = 0; i < N; i++) {
        int x;
        std::cin >> x;

        a.push_back(x);
        s.insert(x);
        if (a.size() == B) {
            l.emplace_back(a, s);
            a.clear();
            s.clear();
        }
    }
    if (a.size()) {
        l.emplace_back(a, s);
    }

    int Q;
    std::cin >> Q;

    while (Q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int x, y;
            std::cin >> x >> y;
            for (auto it = l.begin(); it != l.end(); it++) {
                auto f = it->second.find(x);
                if (f != it->second.end()) {
                    auto xf = std::find(it->first.begin(), it->first.end(), x);
                    assert(xf != it->first.end());
                    it->first.insert(std::next(xf), y);
                    it->second.insert(y);

                    if (it->first.size() >= 2 * B) {
                        int k = B;
                        s.clear();
                        a.clear();
                        while (k--) {
                            auto t = it->first.back();
                            it->first.pop_back();
                            it->second.erase(t);
                            a.push_back(t);
                            s.insert(t);
                        }
                        std::reverse(a.begin(), a.end());
                        l.insert(std::next(it), std::make_pair(a, s));
                    }

                    break;
                }
            }
        } else {
            int x;
            std::cin >> x;
            for (auto it = l.begin(); it != l.end(); it++) {
                auto f = it->second.find(x);
                if (f != it->second.end()) {
                    auto xf = std::find(it->first.begin(), it->first.end(), x);
                    assert(xf != it->first.end());
                    it->first.erase(xf);
                    it->second.erase(x);
                    if (it->first.size() == 0) {
                        l.erase(it);
                    }
                    break;
                }
            }
        }
    }

    for (auto it = l.begin(); it != l.end(); it++) {
        for (auto p : it->first) {
            std::cout << p << " ";
        }
    }

    return 0;
}
