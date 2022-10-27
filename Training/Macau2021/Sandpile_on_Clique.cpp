#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 5E5 + 100;
using pii = pair<int, int>;

int n, s;
int a0;
int a[MAX_N];

signed main() {
    ios::sync_with_stdio(false);
    // n = 5E5;
    // a[0] = (n - 1) * (n - 1) - 1;
    // s = a[0];
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i], s += a[i];
    if (s > n * (n - 2)) {
        cout << "Recurrent" << endl;
        return 0;
    }

    priority_queue<pii, vector<pii>> que;
    for (int i = 0; i < n; ++i) {
        que.emplace(a[i], i);
    }
    while (!que.empty()) {
        int u = que.top().second;
        int w = que.top().first;
        que.pop();
        if (w != a[u]) continue;
        w += a0;
        if (w < n - 1) break;
        int t = w / (n - 1);
        a0 += t;
        a[u] -= t * n;
        que.emplace(a[u], u);
    }
    for (int i = 0; i < n; ++i) {
        cout << a[i] + a0 << ' ';
    }
    cout << endl;

    return 0;
}