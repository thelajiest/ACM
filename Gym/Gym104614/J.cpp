#include <bits/stdc++.h>

using i64 = std::int64_t;

constexpr int N = 52;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> list(N);
    std::vector<std::string> cur;
    for (int i = 0; i < N; i++) std::cin >> list[i];

    for (int i = 0; i < N; i++) {
        cur.push_back(list[i]);
        while (true) {
            auto del1 = [&]() -> bool {
                for (int j = cur.size() - 1; j - 3 >= 0; j--) {
                    if (cur[j][0] == cur[j - 3][0]) {
                        std::vector<std::string> ret;
                        for (int k = 0; k < cur.size(); k++) {
                            if (j - 3 <= k && k <= j) continue;
                            ret.push_back(cur[k]);
                        }
                        std::swap(cur, ret);
                        return true;
                    }
                }
                return false;
            };
            auto del2 = [&]() -> bool {
                for (int j = cur.size() - 1; j - 3 >= 0; j--) {
                    if (cur[j][1] == cur[j - 3][1]) {
                        std::vector<std::string> ret;
                        for (int k = 0; k < cur.size(); k++) {
                            if (j - 3 == k || k == j) continue;
                            ret.push_back(cur[k]);
                        }
                        std::swap(cur, ret);
                        return true;
                    }
                }
                return false;
            };
            if (del1()) continue;
            if (!del2()) {
                break;
            }
        }
    }

    std::cout << cur.size() << " ";
    for (auto p : cur) std::cout << p << " ";

    return 0;
}