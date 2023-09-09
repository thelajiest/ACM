#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAX_N = 1e6 + 7;

int T;
string s;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> s;
        int n = s.size();
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += i * (i + 1) / 2;
        }
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                ans += n - i;
            }
            if (i > 0 && s[i] == s[i - 1]) {
                ans += i * (n - i);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}