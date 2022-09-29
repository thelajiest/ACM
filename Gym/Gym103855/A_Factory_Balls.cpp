#include <bits/stdc++.h>
#define int long long

using namespace std;

const int INF = 1e18;
const int MAX_N = 10;
int dp[(1 << MAX_N) + 3][(1 << MAX_N) + 3];
bool vis[(1 << MAX_N) + 3][(1 << MAX_N) + 3];
int c[MAX_N], ep[MAX_N];
int n, m, k;
int S, T;

int dfs(int s, int t) {
    if (vis[s][t]) return dp[s][t];
    vis[s][t] = true;
    if (s == (S - 1) && t == 0) {
        return dp[s][t] = 0;
    }
    int st = 0;
    for (int i = 0; i < m; ++i) {
        if ((t >> i) & 1) {
            st |= ep[i];
        }
    }
    for (int i = 1; i <= k; ++i) {
        int nxt_st = s;
        for (int j = 0; j < n; ++j) {
            if ((st >> j) & 1) {
                continue;
            }
            if (c[j] == i) {
                nxt_st |= (1 << j);
            } else {
                nxt_st &= ~(1 << j);
            }
        }
        dp[s][t] = min(dp[s][t], dfs(nxt_st, t) + 1);
    }
    for (int i = 0; i < m; ++i) {
        if ((t >> i) & 1) {
            continue;
        }
        dp[s][t] = min(dp[s][t], dfs(s, t | (1 << i)) + 1);
    }
    for (int i = 0; i < m; ++i) {
        if ((t >> i) & 1) {
            dp[s][t] = min(dp[s][t], dfs(s, t & (~(1 << i))) + 1);
        }
    }
    // cout << "dp[" << s << "]" << "[" << t << "] = " << dp[s][t] << endl;
    return dp[s][t];
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> k >> m;
    for (int i = 0; i < n; ++i) cin >> c[i];
    for (int i = 0; i < m; ++i) {
        int num, st = 0;
        cin >> num;
        for (int j = 0; j < num; ++j) {
            int p;
            cin >> p;
            --p;
            st |= (1 << p);
        }
        ep[i] = st;
    }
    S = (1 << n), T = (1 << m);
    for (int s = 0; s < S; ++s) {
        for (int t = 0; t < T; ++t) {
            dp[s][t] = INF;
        }
    }
    int st = 0;
    for (int i = 0; i < n; ++i) {
        if (c[i] == 1) {
            st |= (1 << i);
        }
    }
    dfs(st, 0);
    if (dp[st][0] >= INF) {
        cout << "-1\n";
    } else {
        cout << dp[st][0] << "\n";
    }
    return 0;
}