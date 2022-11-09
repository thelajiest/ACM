#include <bits/stdc++.h>
// #define int long long
// #define sleepy

using namespace std;

const int INF = 1e9;
const int MAX_N = 2e3 + 7;
const int MAX_NM = 4e6 + 7;
vector<int> e[MAX_NM];
int which[MAX_NM], cnt[MAX_NM], w[MAX_NM];
int n, m;
int tot;

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int st = -1, ed = -1;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m;) {
            int k = j;
            if (s[k] == '@') {
                which[i * m + k] = -1;
                ++j;
                continue;
            }
            while (k < m && s[k] != '@') {
                if (s[k] == 'S') st = tot;
                if (s[k] == 'E') ed = tot;
                which[i * m + k] = tot;
                cnt[tot] += (s[k++] == 'm');
            }
            ++tot;
            j = k;
        }
    }
    assert(st != -1 && ed != -1);
    vector<int> in_deg;
    in_deg.resize(tot);
#ifdef sleepy
    cerr << st << ", " << ed << endl;
#endif
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int now = which[i * m + j];
            if (now == -1) continue;
            int ii = i + 1, jj = j;
            if (ii >= n) continue;
            int to = which[ii * m + jj];
            if (to == -1) continue;
            e[now].emplace_back(to);
            ++in_deg[to];
        }
    }
#ifdef sleepy
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cerr << which[i * m + j] << " ";
        }
        cerr << endl;
    }
    for (int i = 0; i < tot; ++i) {
        cerr << i << ": ";
        for (auto p : e[i]) {
            cerr << p.first << ' ';
        }
        cerr << endl;
    }
#endif
    queue<int> q;
    for (int i = 0; i < tot; ++i) {
        w[i] = -INF;
        if (!in_deg[i]) {
            q.push(i);
        }
    }
    w[st] = cnt[st];
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : e[u]) {
            w[v] = max(w[v], cnt[v] + w[u]);
            --in_deg[v];
            if (!in_deg[v]) q.push(v);
        }
    }
    if (w[ed] >= 0) {
        cout << w[ed] << "\n";
    } else {
        cout << "-1\n";
    }
    return 0;
}
