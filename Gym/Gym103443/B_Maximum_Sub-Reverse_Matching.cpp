#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1E3 + 7;
int T, n;
char x[MAX_N], y[MAX_N];
int sub[MAX_N], rev[MAX_N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    while (T--) {
        cin >> n >> (x + 1) >> (y + 1);
        for (int i = 0; i < MAX_N; ++i) sub[i] = rev[i] = 0;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (x[i] == y[i]) {
                ans += 1;
            }
            sub[i] = ans;
        }
        ans = 0;
        for (int i = n; i >= 1; --i) {
            if (x[i] == y[i]) {
                ans += 1;
            }
            rev[i] = ans;
        }
        cout << ans << ' ';

        // int cnt = 0;

        int a = 1, b = 1;
        ans = 0;
        for (int k = 2; k <= 2 * n; ++k) {
            int tmp = 0;
            for (int d = k & 1; d <= n - 1; d += 2) {
                int bb = (k + d) / 2;
                int aa = k - bb;
                if (aa <= 0 || bb > n) break;
                // cerr << aa << ' ' << bb << endl;
                // cnt += 1;
                if (x[aa] == y[bb]) tmp += 1;
                if (aa != bb && x[bb] == y[aa]) tmp += 1;
                if (tmp + sub[aa - 1] + rev[bb + 1] > ans) {
                    ans = tmp + sub[aa - 1] + rev[bb + 1];
                    a = aa;
                    b = bb;
                } else if (tmp + sub[aa - 1] + rev[bb + 1] == ans) {
                    if (bb - aa < b - a) {
                        a = aa;
                        b = bb;
                    } else if (bb - aa == b - a) {
                        if (aa < a) {
                            a = aa;
                            b = bb;
                        }
                    }
                }
                // cerr << k << ':' << aa << ' ' << bb << ' ' << x[aa] << ' '
                //      << x[bb] << ' ' << y[aa] << ' ' << y[bb] << ' ' << tmp
                //      << endl;
            }
        }
        // cerr << cnt << ' ' << n * (n + 1) / 2 << endl;
        cout << ans << ' ' << a << ' ' << b << '\n';
    }

    return 0;
}