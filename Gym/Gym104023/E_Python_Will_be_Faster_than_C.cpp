#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, k;
int a1, a2;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        a1 = a2;
        cin >> a2;
    }
    if (a2 - a1 >= 0) {
        cout << "Python will never be faster than C++" << endl;
    } else {
        int ans = n;
        while (a2 >= k) {
            int tmp = a2;
            a2 = max(0ll, 2 * a2 - a1);
            a1 = tmp;
            // cerr << a2 << endl;
            ans += 1;
        }
        cout << "Python 3." << ans << " will be faster than C++ " << endl;
    }

    return 0;
}