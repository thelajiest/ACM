/*你的愛會將我灌醉*/
#include <bits/stdc++.h>
#define int long long

using namespace std;

int T, x, y;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cin >> x >> y;
        vector<int> a[2], b[2];
        int len = 0;
        while (x) {
            int now = x & 1;
            x >>= 1;
            if (now) {
                a[len & 1].emplace_back(len);
            }
            ++len;
        }
        len = 0;
        while (y) {
            int now = y & 1;
            y >>= 1;
            if (now) {
                b[len & 1].emplace_back(len);
            }
            ++len;
        }
        int ans = 0;
        bool flag = true;
        if (a[0].size() != b[0].size()) {
            flag = false;
        } else {
            for (int i = 0; i < a[0].size(); ++i) {
                ans += abs(a[0][i] - b[0][i]);
            }
        }
        if (a[1].size() != b[1].size()) {
            flag = false;
        } else {
            for (int i = 0; i < a[1].size(); ++i) {
                ans += abs(a[1][i] - b[1][i]);
            }
        }
        cout << "Case " << cas << ": ";
        if (flag) {
            cout << ans / 2 << "\n";
        } else {
            cout << "-1\n";
        }
    }
}