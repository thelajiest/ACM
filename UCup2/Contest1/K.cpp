#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 1E5 + 100;

int T;
int n, m;
int cur[100];

void cal(int x) {
    int ret = 0;
    for (int bit = 1, i = 0; bit <= x; bit <<= 1, ++i) {
        if (x & bit) ret = i;
    }
    cur[ret] += 1;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < 100; ++i) cur[i] = 0;
        int ans = 0;
        while (n--) {
            int x;
            cin >> x;
            cal(x);
        }
        for (int i = 0; i < 100; ++i) {
            ans = max(ans, cur[i]);
        }
        cout << ans << '\n';
    }

    return 0;
}