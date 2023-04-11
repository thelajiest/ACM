#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> s(n);
    for (auto& p : s) std::cin >> p;

    auto solve = [](std::string s) -> std::string {
        int n = s.size();

        std::string ret;
        for (int i = 0, j; i < n; i = j) {
            j = i;
            if (s[i] == 'T') {
                while (j < n && s[j] == 'T') j++;
                int len = j - i;
                for (int j = 0; j < len / 2; j++) {
                    ret += "PC";
                }
                if (len % 2 == 1) ret += "T";
            } else {
                ret += s[i];
                j++;
            }
        }
        return ret;
    };

    for (auto& p : s) p = solve(p);
    for (auto p : s) {
        std::cout << p << '\n';
    }
    return 0;
}