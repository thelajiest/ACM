#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAX_N = 2E6 + 100;
using pii = pair<int, int>;
using piii = pair<pii, int>;

const int x[19] = {1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5};
const int y[19] = {1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 4, 5, 2, 3, 4, 5, 3, 4, 5};
const int n_x[6] = {-1, -1, 0, 0, 1, 1};
const int n_y[6] = {-1, 0, -1, 1, 0, 1};
bool vaild[10][10];
int code[10][10];

int n;
int score[MAX_N];
int dp[MAX_N];
bool vis[MAX_N];
vector<piii> G[19];

int input_state() {
    int ret = 0;
    string s;
    for (int i = 0; i < 5; ++i) {
        cin >> s;
        for (char c : s) {
            ret >>= 1;
            if ('#' == c) ret += (1 << 18);
        }
    }
    return ret;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < 19; ++i) cin >> score[i];
    for (int i = 0; i < 19; ++i) vaild[x[i]][y[i]] = true, code[x[i]][y[i]] = i;
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 6; ++j) {
            int x1 = x[i] + n_x[j], x2 = x[i] + n_x[j] * 2;
            int y1 = y[i] + n_y[j], y2 = y[i] + n_y[j] * 2;
            if (vaild[x1][y1] && vaild[x2][y2]) {
                G[i].emplace_back(pii(code[x1][y1], code[x2][y2]),
                                  score[code[x1][y1]]);
            }
        }
    }
    // for (int i = 0; i < 19; ++i) {
    //     for (piii it : G[i]) {
    //         cerr << it.first.first << ' ' << it.first.second << ' ' <<
    //         it.second
    //              << endl;
    //     }
    // }

    queue<int> que;
    vis[0] = true;
    que.push(0);
    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i = 0; i < 19; ++i) {
            if (0 == (u & (1 << i))) {
                int v = u ^ (1 << i);
                if (dp[v] < dp[u]) dp[v] = dp[u];
                if (!vis[v]) {
                    que.push(v);
                    vis[v] = true;
                }
            } else {
                for (piii it : G[i]) {
                    int v1 = it.first.first;
                    int v2 = it.first.second;
                    int w = it.second;
                    if (0 != (u & (1 << v1)) || 0 != (u & (1 << v2))) continue;
                    int v = u ^ (1 << i) ^ (1 << v1) ^ (1 << v2);

                    // if (u == (1 << 0)) {
                    //     cerr << v1 << ' ' << v2 << endl;
                    //     cerr << dp[v] << ' ' << dp[u] << ' ' << w << endl;
                    //     cerr << endl;
                    // }

                    // cerr << dp[v] << ' ' << dp[u] << ' ' << w << endl;
                    if (dp[v] < dp[u] + w) dp[v] = dp[u] + w;
                    if (!vis[v]) {
                        que.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
    }

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << dp[input_state()] << '\n';
    }

    return 0;
}