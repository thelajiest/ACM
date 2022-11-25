#include <bits/stdc++.h>
#define sleepy

using namespace std;

const int MAX_N = 18;
int dp[1 << MAX_N][MAX_N];
bool vis[1 << MAX_N][MAX_N];
int a[MAX_N][MAX_N];
string str[MAX_N];
int n;

int dfs(int s, int i) {
    if (vis[s][i]) return dp[s][i];
    vis[s][i] = true;
    int res = 0;
    for (int j = 0; j < n; ++j) {
        if ((s >> j) & 1) {
            continue;
        }
        if (!a[i][j]) continue;
        res |= !dfs(s | (1 << j), j);
        if (res) break;
    }
#ifdef sleepy
    // cerr << s << ", " << i << ": " << res << endl;
#endif
    return dp[s][i] = res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> str[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (str[i][(int)str[i].size() - 1] == str[j][0]) {
                a[i][j] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans |= !dfs(1 << i, i);
        if (ans) break;
    }
    if (ans) {
        cout << "First\n";
    } else {
        cout << "Second\n";
    }
    return 0;
}