#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100 + 7;
int T, n, m, s, t;
int G[MAX_N][MAX_N];
int ans[MAX_N];
// 0当前未考虑到，2到达后无论无如何join胜利，1join先到达后必胜否则必败

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> s >> t;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                G[i][j] = 0;
            }
        }
        for (int i = 1; i <= n; ++i) {
            ans[i] = 0;
        }

        while (m--) {
            int u, v;
            cin >> u >> v;
            G[v][u] += 1;  // 反向建边s
        }

        ans[t] = 2;
        queue<int> que;
        que.push(t);
        while (!que.empty()) {
            int u = que.front();
            que.pop();

            for (int v = 1; v <= n; ++v) {
                if (2 == ans[v] || 0 == G[u][v]) continue;
                if (1 == ans[v]) {
                    ans[v] = 2;
                    que.push(v);
                } else {
                    if (G[u][v] >= 2) {
                        ans[v] = 2;
                        que.push(v);
                    } else if (1 == G[u][v]) {
                        ans[v] = 1;
                        que.push(v);
                    }
                }
            }
        }

        if (2 == ans[s]) {
            cout << "Join Player\n";
        } else {
            cout << "Cut Player\n";
        }
    }

    return 0;
}