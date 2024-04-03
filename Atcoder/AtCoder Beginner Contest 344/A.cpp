#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    std::vector<int> a;
    std::string ans;

    int ok = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 's') {
            ok += 1;
        }
        if (ok == 0 || ok == 2) {
            if (s[i] != '|') ans += s[i];
        }
    }

    std::cout << ans << std::endl;

    return 0;
}