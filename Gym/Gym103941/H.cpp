#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAX_M = 1e5 + 7;
char s[MAX_M << 1];
bool vis[MAX_M << 1][4];
int T, m, x, y;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> m >> x >> y;
        cin >> s;
        cin >> s + m;
        for (int i = 1; i <= m * 2; ++i) {
            for (int j = 0; j < 4; ++j) {
                vis[i][j] = false;
            }
        }
        queue<pii> q;
        q.push(make_pair(x, 0));
        bool flag = false;
        while (!q.empty()) {
            pii p = q.front();
            q.pop();
            int u = p.first, d = p.second;
            if (vis[u][d]) continue;
            vis[u][d] = true;
            if (s[u - 1] == 'I') {
                if (u == m + y) {
                    if (d == 0) {
                        flag = true;
                        break;
                    } else {
                        continue;
                    }
                }
                int nxt_u = u;
                if (d == 0) {
                    nxt_u += m;
                } else if (d == 1) {
                    nxt_u -= 1;
                } else if (d == 2) {
                    nxt_u -= m;
                } else if (d == 3) {
                    nxt_u += 1;
                }
                if (nxt_u < 1 || nxt_u > m * 2) continue;
                if (u == 1 && d == 1) continue;
                if (u == m && d == 3) continue;
                if (u == m + 1 && d == 1) continue;
                if (u == m * 2 && d == 3) continue;
                if (vis[nxt_u][d]) continue;
                q.push(make_pair(nxt_u, d));
            } else {
                if (u == m + y) {
                    if (d == 1 || d == 3) {
                        flag = true;
                        break;
                    } else {
                        continue;
                    }
                }
                if (d == 0 || d == 2) {
                    if (u != m && u != m * 2) {
                        if (!vis[u + 1][3]) {
                            q.push(make_pair(u + 1, 3));
                        }
                    }
                    if (u != 1 && u != m + 1) {
                        if (!vis[u - 1][1]) {
                            q.push(make_pair(u - 1, 1));
                        }
                    }
                } else if (d == 1 || d == 3) {
                    if (u - m > 0) {
                        if (!vis[u - m][2]) {
                            q.push(make_pair(u - m, 2));
                        }
                    }
                    if (u + m <= m * 2) {
                        if (!vis[u + m][0]) {
                            q.push(make_pair(u + m, 0));
                        }
                    }
                }
            }
        }
        if (flag) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        for (int i = 1; i <= m * 2; ++i)
            for (int j = 0; j < 4; ++j) vis[i][j] = false;
    }
    return 0;
}