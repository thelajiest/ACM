#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    constexpr double INF = numeric_limits<double>::max();
    vector<vector<double>> mp(n + m + 1, vector<double>(n + m + 1, INF));

    vector<pair<double, double>> cnt;
    cnt.push_back({0, 0});
    for (int i = 0; i < n + m; i++) {
        double x, y;
        cin >> x >> y;
        cnt.emplace_back(x, y);
    }

    for (int i = 0; i <= n + m; i++) {
        auto [x, y] = cnt[i];
        for (int j = 0; j <= n + m; j++) {
            auto [xx, yy] = cnt[j];
            mp[i][j] = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
        }
        mp[i][i] = 0;
    }

    vector<vector<double>> dp((1 << (n + m + 1)),
                              vector<double>(n + m + 1, INF));
    dp[1][0] = 0;
    for (int s = 0; s < (1 << (n + m + 1)); s++) {
        for (int i = 0; i <= n + m; i++) {
            double speed = 1;
            for (int j = n + 1; j <= n + m; j++) {
                if ((s ^ (1 << i)) & (1 << j)) speed *= 2;
            }
            if (s & (1 << i)) {
                for (int j = 0; j <= n + m; j++)
                    if (j != i && (s & (1 << j)))
                        dp[s][i] = min(dp[s][i],
                                       dp[s ^ (1 << i)][j] + mp[j][i] / speed);
            }
        }
    }
    double ans = INF;
    for (int i = 1; i <= n + m; i++) {
        for (int j = 0; j < (1 << m); j++) {
            double speed = 1;
            for (int t = 0; t < m; t++)
                if (j & (1 << t)) speed *= 2;
            ans = min(ans, dp[(((1 << (n + 1)) - 1)) | (j << (n + 1))][i] +
                               mp[i][0] / speed);
        }
    }
    cout << fixed << setprecision(10);
    cout << ans << endl;

    return 0;
}