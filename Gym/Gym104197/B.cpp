#include <bits/stdc++.h>

using i64 = std::int64_t;

void bruteForce() {
    int n, k;
    std::cin >> n >> k;

    std::set<std::vector<int>> store;
    for (int i = 0; i < (1 << n); i++) {
        std::vector<int> a(n);
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) a[j] = 1;
        }
        std::vector<int> f(n);
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int t = 0; t < k; t++) {
                sum += a[(j + t) % n];
            }
            f[j] = sum;
        }
        store.insert(f);
    }

    std::cout << store.size() << std::endl;
    // sum(i,2) = 2 ^(i-1)  -1
}
void solve() {}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        // solve();
        bruteForce();
    }

    return 0;
}