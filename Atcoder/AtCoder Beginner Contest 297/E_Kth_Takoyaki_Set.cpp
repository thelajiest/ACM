#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::sort(begin(a), end(a));
    std::priority_queue<i64, std::vector<i64>, std::greater<i64>> Q;

    Q.push(0);
    std::vector<i64> b;

    std::map<i64, int> mp;

    while (b.size() <= k) {
        auto cur = Q.top();
        mp[cur] = 1;
        b.push_back(cur);
        Q.pop();
        for (auto next : a) {
            if (mp[next + cur] == 0) {
                Q.push(next + cur);
                mp[next + cur] = 1;
            }
        }
    }

    std::cout << b.back();

    return 0;
}