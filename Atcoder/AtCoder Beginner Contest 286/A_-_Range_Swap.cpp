#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    std::cin >> n;

    int p, q, l, r;

    std::cin >> p >> q >> l >> r;
    p--, l--;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::swap_ranges(a.begin() + p, a.begin() + q, a.begin() + l);

    for (int i = 0; i < static_cast<int>(a.size()); i++) {
        std::cout << a[i] << " \n"[i == static_cast<int>(a.size()) - 1];
    }

    return 0;
}