#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = " " + s;

    vector<array<int, 2>> sum(n + 1, array<int, 2>());

    for (int i = 1; i <= n; i++) {
        sum[i][0] += sum[i - 1][0] + (s[i] == '0');
        sum[i][1] += sum[i - 1][1] + (s[i] == '1');
    }

    int ans = 0;
    for (int i = 1; i + k - 1 <= n; i++) {
        int l = i, r = i + k - 1;
        if (sum[r][1] - sum[l - 1][1] == sum[n][1] &&
            sum[r][0] - sum[l - 1][0] == 0)
            ans++;
    }

    if (sum[n][1] > k) ans = 0;

    if (ans == 1)
        cout << "Yes\n";
    else
        cout << "No\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}