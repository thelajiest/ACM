#include <bits/stdc++.h>
using i64 = std::int64_t;

constexpr int B = 1000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;

    std::vector<int> p;
    std::cin >> N;
    std::vector<int> num(N);
    for (int i = 0; i < N; i++) {
        std::cin >> num[i];
        p.push_back(num[i]);
    }

    std::cin >> Q;
    std::vector<std::tuple<int, int, int>> query(Q);
    for (int i = 0; i < Q; i++) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int x, y;
            std::cin >> x >> y;
            query[i] = {op, x, y};
            p.push_back(y);
        } else {
            int x;
            std::cin >> x;
            query[i] = {op, x, 0};
        }
    }

    std::sort(p.begin(), p.end());
    p.resize(std::unique(p.begin(), p.end()) - p.begin());
    int m = p.size();

    std::list<std::pair<std::vector<int>, std::vector<int>>> l;

    std::vector<int> a;
    std::vector<int> s(m + 1, 0);
    for (int i = 0; i < N; i++) {
        int x;
        x = num[i];

        a.push_back(x);
        int xt = std::lower_bound(p.begin(), p.end(), x) - p.begin();
        s[xt] = 1;

        if (a.size() == B) {
            l.emplace_back(a, s);
            a.clear();
            std::fill(s.begin(), s.end(), 0);
        }
    }
    if (a.size()) {
        l.emplace_back(a, s);
    }

    for (auto [op, x, y] : query) {
        if (op == 1) {
            int xt = std::lower_bound(p.begin(), p.end(), x) - p.begin();
            int yt = std::lower_bound(p.begin(), p.end(), y) - p.begin();
            for (auto it = l.begin(); it != l.end(); it++) {
                if (it->second[xt] == 1) {
                    auto xf = std::find(it->first.begin(), it->first.end(), x);
                    it->first.insert(std::next(xf), y);
                    it->second[yt] = 1;

                    if (it->first.size() > 2 * B) {
                        int k = B;
                        std::fill(s.begin(), s.end(), 0);
                        a.clear();
                        while (k--) {
                            auto t = it->first.back();
                            int tt = std::lower_bound(p.begin(), p.end(), t) -
                                     p.begin();
                            it->first.pop_back();
                            it->second[tt] = 0;
                            a.emplace_back(t);
                            s[tt] = 1;
                        }
                        std::reverse(a.begin(), a.end());
                        l.insert(std::next(it), std::make_pair(a, s));
                    }

                    break;
                }
            }
        } else {
            int xt = std::lower_bound(p.begin(), p.end(), x) - p.begin();
            for (auto it = l.begin(); it != l.end(); it++) {
                if (it->second[xt] == 1) {
                    auto xf = std::find(it->first.begin(), it->first.end(), x);
                    it->first.erase(xf);
                    it->second[xt] = 0;

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
