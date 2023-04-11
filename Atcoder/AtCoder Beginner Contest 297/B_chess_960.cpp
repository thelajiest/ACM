#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    int n = s.size();
    s = " " + s;
    int r1(0), r2(0), k;
    int b1(0), b2(0);
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'R' && r1 == 0) r1 = i;
        if (s[i] == 'R' && r1 != 0) r2 = i;
        if (s[i] == 'K') k = i;
        if (s[i] == 'B' && b1 == 0) b1 = i;
        if (s[i] == 'B' && b1 != 0) b2 = i;
    }
    if (r1 <= k && k <= r2 && ((b1 + b2) % 2 == 1))
        std::cout << "Yes";
    else
        std::cout << "No";
    return 0;
}