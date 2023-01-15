#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> ans;
    std::string d;
    auto dfs = [&](auto&& self, char cur, int len) {
        if (len == 6) {
            ans.push_back(d);
            return;
        }

        for (char i = '0'; i <= '9'; i++) {
            d.push_back(i);
            self(self, i, len + 1);
            d.pop_back();
        }
    };

    for (char i = '1'; i <= '9'; i++) {
        d.push_back(i);
        dfs(dfs, i, 1);
        d.pop_back();
    }

    // std::sort(begin(ans), end(ans));

    auto p = ans[n - 1];

    std::cout << p[0] << p[0] << p[1] << p[2] << p[3] << p[3] << p[4] << p[5]
              << p[4] << std::endl;
    return 0;
}