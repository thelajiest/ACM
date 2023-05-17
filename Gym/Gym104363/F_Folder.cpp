#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> p(n);

    for (int i = 0; i < n - 1; i++) {
        int x;
        std::cin >> x;
        x--;
        p[x]++;
    }

    int leaf = std::count(begin(p), end(p), 0);

    std::cout << leaf - 1 << std::endl;

    return 0;
}