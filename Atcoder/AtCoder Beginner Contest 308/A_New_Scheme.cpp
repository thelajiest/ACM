#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 8;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    bool ok = std::is_sorted(begin(a), end(a));

    for (int i = 0; i < n; i++) {
        ok &= ((100 <= a[i]) && (a[i] <= 675) && (a[i] % 25 == 0));
    }

    if (ok)
        std::cout << "Yes\n";
    else
        std::cout << "No\n";

    return 0;
}