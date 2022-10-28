#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto& it : a)
        for (auto& it2 : it) cin >> it2;

    vector<int> ml(n), mh(m);
    for (int i = 0; i < n; i++) {
        ml[i] = *min_element(a[i].begin(), a[i].end());
    }
    for (int j = 0; j < m; j++) {
        int mn = numeric_limits<int>::max();
        for (int i = 0; i < n; i++) {
            mn = min(mn, a[i][j]);
        }
        mh[j] = mn;
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == ml[i] && a[i][j] == mh[j]) ans++;

    cout << ans << endl;
    return 0;
}