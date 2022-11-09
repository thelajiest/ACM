#include <bits/stdc++.h>
#define int long long
// #define sleepy

using namespace std;

const int INF = 1e18;
const int MAX_N = 3e2 + 7;
int dp1[MAX_N][MAX_N], dp2[MAX_N][MAX_N];
int c[MAX_N], w[MAX_N];
int edge[MAX_N][MAX_N];
int T, n, m;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> c[i];
        for (int i = 1; i <= n; ++i) cin >> w[i];
        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            edge[u][v] = edge[v][u] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp2[i][j] = INF;
                if (edge[i][j] && c[i] == c[j]) {
                    dp1[i][j] = w[j];
                } else {
                    dp1[i][j] = INF;
                }
            }
            dp1[i][i] = 0;
        }
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (c[i] == c[j] && c[i] == c[k]) {
                        dp1[i][j] = min(dp1[i][j], dp1[i][k] + dp1[k][j]);
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dp1[i][j] < INF) {
                    dp1[i][j] += w[i];
                }
            }
        }
#ifdef sleepy
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dp1[i][j] < INF)
                    cerr << dp1[i][j] << " ";
                else
                    cerr << "0 ";
            }
            cerr << "\n";
        }
#endif
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= n; ++k) {
                    if (edge[j][k] && c[j] != c[k]) {
                        dp2[i][k] = min(dp2[i][k], dp1[i][j] + w[k]);
                    }
                }
            }
        }
#ifdef sleepy
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dp2[i][j] < INF)
                    cerr << dp2[i][j] << " ";
                else
                    cerr << "0 ";
            }
            cerr << "\n";
        }
#endif
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    dp2[i][j] = min(dp2[i][j], max(dp2[i][k], dp2[k][j]));
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j) {
                    cout << "0 ";
                    continue;
                }
                int ans = min(dp1[i][j], dp2[i][j]);
                for (int k = 1; k <= n; ++k) {
                    ans = min(ans, max(dp2[i][k], dp1[k][j]));
                }
                cout << ans << " ";
            }
            cout << "\n";
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                edge[i][j] = 0;
            }
        }
    }
    return 0;
}