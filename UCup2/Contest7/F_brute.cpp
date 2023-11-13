#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    const int N = (1 << n);
    std::vector<std::vector<int>> adj(N);

    for (int i = 1; i < N; i++) {
        if (__builtin_popcount(i) != k) continue;
        for (int j = 1; j < N; j++) {
            if (__builtin_popcount(j) != k) continue;
            auto check = [&](int x, int y) {
                std::vector<int> cntx(n, 0);
                for (int i = 0; i < n; i++) {
                    if ((x >> i) & 1) cntx[i] = 1;
                }
                std::vector<int> cnty(n, 0);
                for (int i = 0; i < n; i++) {
                    if ((y >> i) & 1) cnty[i] = 1;
                }
                for (int i = 0; i < n; i++) {
                    if (cntx[i] && cntx[(i + 2) % n]) return false;
                }
                for (int i = 0; i < n; i++) {
                    if (cnty[i] && cnty[(i + 2) % n]) return false;
                }
                for (int i = 0; i < n; i++) {
                    if (cntx[i] && (cnty[(i + 1) % n] || cnty[(i + 8) % n]))
                        return false;
                }
                return true;
            };
            if (check(i, j)) {
                adj[i].push_back(j);
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (adj[i].size() != 0) cnt++;
    }

    std::cerr << cnt << std::endl;
    std::vector<int> t;
    auto dfs = [&](auto&& self, int h, int mask, int l1, int l2) -> void {
        t.push_back(mask);
        if (h == m) {
            auto check = [&]() -> bool {
                auto mp = [&](int i, int j) { return (!(t[i] >> j & 1)); };
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        if (mp(i, j) == 1) {
                            int up = mp((i - 1 + n) % n, j);
                            int down = mp((i + 1) % n, j);
                            int left = mp(i, (j - 1 + m) % m);
                            int right = mp(i, (j + 1) % m);
                            if (up + down + left + right != 3) {
                                return false;
                            }
                        }
                    }
                }

                return true;
            };
            if (check()) {
                std::cout << "fuck!!!" << std::endl;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        std::cout << (!((t[i] >> j) & 1));
                    }
                    std::cout << '\n';
                }
                exit(0);
            }

            t.pop_back();
            return;
        }
        for (const auto& next : adj[mask]) {
            if (l2 != -1 && __builtin_popcount(l2 & next) != 0) continue;
            self(self, h + 1, next, mask, l1);
        }
        t.pop_back();
    };

    for (int i = 0; i < N; i++) {
        if (adj[i].size() >= 1) {
            dfs(dfs, 0, i, -1, -1);
            cnt--;
            std::cerr << cnt << std::endl;
        }
    }

    return 0;
}