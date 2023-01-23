#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr i64 INF = std::numeric_limits<i64>::max() / 3.0;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    std::cin >> n;

    std::vector<i64> val(n);

    for (int i = 0; i < n; i++) std::cin >> val[i];

    std::vector<std::vector<i64>> mp(n, std::vector<i64>(n, INF));
    std::vector<std::vector<i64>> cost(n, std::vector<i64>(n, 0));

    for (int i = 0; i < n; i++) {
        std::string in;
        std::cin >> in;
        for (int j = 0; j < n; j++) {
            if (in[j] == 'Y') mp[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (i != j) cost[i][j] = val[i] + val[j];
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mp[i][k] + mp[k][j] < mp[i][j]) {
                    mp[i][j] = mp[i][k] + mp[k][j];
                    cost[i][j] = cost[i][k] + cost[k][j] - val[k];
                } else if (mp[i][k] + mp[k][j] == mp[i][j]) {
                    cost[i][j] =
                        std::max(cost[i][j], cost[i][k] + cost[k][j] - val[k]);
                }
            }
        }

        int q;
        std::cin >> q;
        while (q--) {
            int u, v;
            std::cin >> u >> v;
            u--, v--;
            if (mp[u][v] >= INF)
                std::cout << "Impossible\n";
            else
                std::cout << mp[u][v] << " " << cost[u][v] << '\n';
        }

        return 0;
    }