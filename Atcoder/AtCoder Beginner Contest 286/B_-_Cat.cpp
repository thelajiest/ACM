#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::string s, ans;

    std::cin >> s;

    int i = 0;
    for (; i < n - 1;) {
        if (s[i] == 'n' && s[i + 1] == 'a') {
            i += 2;
            ans += "nya";
        } else {
            ans += s[i];
            i += 1;
        }
    }
    if (i == n - 1) {
        ans += s[i];
    }
    std::cout << ans << std::endl;

    return 0;
}