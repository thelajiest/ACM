#include <bits/stdc++.h>
using namespace std;

#define int long long

int T;
int r, b, s, d;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> b >> r >> d >> s;
        if (0 == r && d != 0) {
            cout << "gua!" << '\n';
        } else if ((s * r / 60 + 1) * b < d) {
            cout << "gua!" << '\n';
        } else {
            cout << "ok" << '\n';
        }
    }

    return 0;
}
