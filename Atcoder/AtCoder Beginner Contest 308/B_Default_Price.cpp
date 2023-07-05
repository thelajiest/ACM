#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> l(n);
    for (auto& it : l) std::cin >> it;

    std::vector<std::string> d(m);
    for (auto& it : d) std::cin >> it;

    std::vector<int> p(m);

    int p0;
    std::cin >> p0;
    for (auto& it : p) std::cin >> it;

    std::map<std::string, int> mp;
    for (int i = 0; i < m; i++) {
        mp[d[i]] = p[i];
    }

    int ans = 0;
    for (auto _ : l) {
        if (mp.find(_) != mp.end())
            ans += mp[_];
        else
            ans += p0;
    }

    std::cout << ans << std::endl;

    return 0;
}