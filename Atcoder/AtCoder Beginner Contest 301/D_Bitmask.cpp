#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    std::reverse(begin(s), end(s));

    i64 N;
    std::cin >> N;

    int n = s.size();

    i64 ans = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1') ans |= (1LL << i);
    }
    if (ans > N) {
        std::cout << "-1";
        return 0;
    } else {
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '?')
                if ((ans | (1LL << i)) <= N) ans |= (1LL << i);
        }
    }

    std::cout << ans;
    return 0;
}