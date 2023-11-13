#include <bits/stdc++.h>
using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    bool flag = true;
    int base;
    for (base = 2; base <= n; base *= 2) {
        int lastbase = base / 2;
        for (int j = lastbase + 1; j <= base; j++) {
            if (j - 1 >= lastbase + 1 && a[j] < a[j - 1]) flag = false;
        }
        if (base * 2 > n) break;
    }
    for (int j = base + 1; j <= n; j++) {
        if (j - 1 >= base + 1 && a[j] < a[j - 1]) flag = false;
    }
    if (flag)
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}