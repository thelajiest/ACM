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
#define int long long

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int MAX_W = 64;
const int INF = 1e18;
const int MOD = 1e9 + 7;

int p2[MAX_W], l[MAX_W], r[MAX_W];
int cnt[MAX_W];

int q, x, y;

int calc(int x) {
    if (x < 4) return 0;
    int res = 0;
    for (int i = 2; i < MAX_W; i++) {
        int low = p2[i], up = min(x, p2[i] * 2 - 1);
        int mid = min(r[i] - 1, up);
        if (low > up) break;
        res = (res + (mid - low + 1) * cnt[i] % MOD) % MOD;
        res = (res + (up - mid) * (cnt[i] + 1) % MOD) % MOD;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    for (int i = 0, prod = 1; i < MAX_W; i++, prod *= 2) {
        p2[i] = prod;
        if (i > 1) {
            for (int j = 0, _prod = 1; _prod <= prod; j++, _prod *= i) {
                l[i] = _prod;
                cnt[i] = j;
                if (_prod > INF / i) {
                    break;
                }
            }
            if (l[i] > INF / i) {
                r[i] = INF + 1;
            } else {
                r[i] = l[i] * i;
            }
        }
    }
    cin >> q;
    while (q--) {
        cin >> x >> y;
        int ans = (calc(y) - calc(x - 1) + MOD) % MOD;
        cout << ans << "\n";
    }
    return 0;
}