#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int>> pos(m + 1);

    for (int i = 1; i <= n; i++) {
        int k = max(0, -(a[i] + i) / i);
        int now = a[i] + k * i;
        while (now <= n && k <= m) {
            pos[k].push_back(now);
            now += i;
            k++;
        }
    }

    for (int i = 1; i <= m; i++) {
        sort(pos[i].begin(), pos[i].end());
        int ans = 0;
        for (auto it : pos[i]) {
            if (it == ans) ans++;
        }
        cout << ans << '\n';
    }

    return 0;
}