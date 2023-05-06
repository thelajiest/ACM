#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    int max = 0;
    for (int i = 0, j; i < n; i = j) {
        j = i;
        if (s[i] == '-') {
            j++;
            continue;
        }
        while (j < n && s[j] == 'o') j++;
        max = std::max(max, j - i);
    }

    if (max == 0 || max == n)
        std::cout << "-1";
    else
        std::cout << max;

    return 0;
}