#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<i64> a(n + 1);
    vector<i64> d(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) d[i] = d[i - 1] + a[i];

    i64 ans = 0;
    for (int i = 1; i <= m; i++) ans += i * a[i];
    i64 res = ans;

    for (int i = 2; i + m - 1 <= n; i++) {
        res -= d[i - 2 + m] - d[i - 2];
        res += m * a[i + m - 1];
        ans = max(ans, res);
    }

    cout << ans << endl;

    return 0;
}