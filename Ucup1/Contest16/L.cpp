#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// #define sleepy
#define int long long

using namespace std;

using pii = pair<int, int>;

const int MAX_N = 5e5 + 7;

pii a[MAX_N];
int p_sum[MAX_N], s_sum[MAX_N];

int T, n, m;

bool cmp(pii &A, pii &B) { return A.first - A.second > B.first - B.second; }

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].first >> a[i].second;
        }
        sort(a + 1, a + n + 1, cmp);
        for (int i = 1; i <= n; ++i) {
            p_sum[i] = p_sum[i - 1] + a[i].first;
        }
        s_sum[n + 1] = 0;
        for (int i = n; i >= 1; i--) {
            s_sum[i] = s_sum[i + 1] + a[i].second;
        }
        int ans = 0;
        for (int i = n; i >= 2; i--) {
            int j = (m - i) / 2;
            if (i + j < n) break;
            // cerr << i << ": " << p_sum[i] << ", " << s_sum[i + 1] << endl;
            ans = max(ans, p_sum[i] + s_sum[i + 1]);
        }
        if ((m + 1) / 2 >= n) {
            ans = max(ans, s_sum[1]);
        }
        cout << ans << "\n";
    }
    return 0;
}