#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// #define sleepy
// #define int long long

using namespace std;

using ll = long long;
using pii = pair<int, int>;

int T, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(begin(a), end(a));
        int l = 0, r = n - 1, x = 0;
        ll ans = 0;
        while (l < r) {
            if (x + a[l] >= a[r]) {
                int inc = a[r] - x;
                a[l] -= inc;
                x += inc;
                a[r] -= x;
                x = 0;
                ans += inc + 1;
            } else {
                int inc = a[l];
                a[l] -= inc;
                x += inc;
                ans += inc;
            }
            if (a[l] == 0) ++l;
            if (a[r] == 0) --r;
        }
        if (a[l] > 0) {
            if (x >= a[l]) {
                ans++;
            } else {
                int inc = (a[l] - x) / 2;
                x += inc, a[l] -= inc;
                ans += inc;
                if (x > 0) a[l] -= x, ans += 1;
                if (a[l] > 0) ans += a[l];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}