#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 7;
int c[MAX_N];
int T, n, m, k;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 0; i < n; ++i) cin >> c[i];
        vector<int> v;
        int cnt = 0;
        while (n > 1 && c[n - 1] == c[0]) ++cnt, --n;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && c[i] == c[j]) ++j, ++cnt;
            v.emplace_back(cnt);
            cnt = 0;
            i = j;
        }
        bool flag = false;
        int ans = 0;
        for (auto u : v) {
            if (u >= k) flag = true;
            ans += (u + k - 1) / k;
        }
        if (flag) {
            cout << ans << "\n";
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}