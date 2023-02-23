#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    int add = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == '+') add++;

    int minus = n - add;

    int q;
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        i64 a, b;
        std::cin >> a >> b;
        if (add == minus) {
            std::cout << "YES\n";
        } else {
            i64 res = 1LL * (minus - add) * b, diff = a - b;
            if (diff == 0 || res % diff != 0) {
                std::cout << "NO\n";
                continue;
            }
            i64 inter = res / diff;
            std::cout << (-minus <= inter && inter <= add ? "YES\n" : "NO\n");
        }
    }

    return 0;
}