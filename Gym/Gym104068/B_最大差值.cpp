#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> num;
    for (int i = 1; i <= 9; i++) {
        int x;
        std::cin >> x;
        for (int j = 0; j < x; j++) num.push_back(i);
    }

    std::sort(begin(num), end(num), std::greater());

    std::vector<int> a, b;

    std::reverse_copy(begin(num), begin(num) + n, std::back_inserter(a));
    std::copy(begin(num) + n, end(num), std::back_inserter(b));

    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (i < m)
            ans.push_back(a[i] - b[i]);
        else
            ans.push_back(a[i]);
    }

    while (ans.back() == 0 && ans.size() != 0) ans.pop_back();
    if (ans.size() == 0) ans.push_back(0);

    std::reverse(begin(ans), end(ans));
    for (auto p : ans) std::cout << p;
    std::cout << std::endl;

    return 0;
}