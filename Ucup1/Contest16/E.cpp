#include <bits/stdc++.h>

using i64 = std::int64_t;

struct node {
    int ls = -1, rs = -1;
    int val = -1;
};

std::vector<int> dp[1003][1003];

std::vector<int> operator+(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> ret;
    std::copy(std::begin(a), std::end(a), std::back_inserter(ret));
    std::copy(std::begin(b), std::end(b), std::back_inserter(ret));

    return ret;
}

bool operator<(const std::vector<int>& a, const std::vector<int>& b) {
    int n = a.size();
    int m = b.size();

    assert(n != 0 && m != 0 && n == m);
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }

    return false;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    std::vector<node> tree(n);
    std::vector<int> size(n);
    for (int i = 0; i < n; i++) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int x, y;
            std::cin >> x >> y;
            x--, y--;
            tree[i] = {x, y, -1};
        } else {
            int val;
            std::cin >> val;
            tree[i] = {-1, -1, val};
        }
    }

    auto dfs = [&](auto&& self, int u, int dep) -> void {
        if (tree[u].ls == -1) {
            dp[u][0] = {tree[u].val};
            size[u] = 0;
            return;
        }
        size[u] = 1;
        self(self, tree[u].ls, dep + 1);
        self(self, tree[u].rs, dep + 1);
        size[u] += size[tree[u].ls];
        size[u] += size[tree[u].rs];
        size[u] = std::min(size[u], m);
        int lu = tree[u].ls, ru = tree[u].rs;
        for (int i = 0; i <= std::min(m, size[lu]); i++) {
            for (int j = 0; j <= std::min(m - i, size[ru]); j++) {
                if (dp[u][i + j].size() == 0)
                    dp[u][i + j] = dp[tree[u].ls][i] + dp[tree[u].rs][j];
                else
                    dp[u][i + j] = std::min(
                        dp[u][i + j], dp[tree[u].ls][i] + dp[tree[u].rs][j]);
                if (i + j + 1 <= std::min(size[u], m)) {
                    if (dp[u][i + j + 1].size() == 0)
                        dp[u][i + j + 1] =
                            dp[tree[u].rs][j] + dp[tree[u].ls][i];
                    else
                        dp[u][i + j + 1] =
                            std::min(dp[u][i + j + 1],
                                     dp[tree[u].rs][j] + dp[tree[u].ls][i]);
                }
            }
        }
    };

    dfs(dfs, 0, 0);

    auto ans = dp[0][m];
    for (int i = 0; i < m; i++) {
        if (i % 2 == m % 2) {
            ans = std::min(ans, dp[0][i]);
        }
    }
    for (auto p : ans) std::cout << p << " ";
    std::cout << std::endl;
    return 0;
}