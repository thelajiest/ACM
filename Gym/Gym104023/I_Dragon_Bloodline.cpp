#include <bits/stdc++.h>
#define int long long
// #define sleepy

using namespace std;

const int MAX_N = 5e4 + 7;
const int MAX_K = 23;
int a[MAX_N], b[MAX_K];
int T, n, k;
vector<int> tmp_b;

bool chk(int x) {
    tmp_b.clear();
    priority_queue<int> q;
    int remain = 0;
    for (int i = 0; i < k; ++i) tmp_b.emplace_back(b[i]), remain += b[i];
    for (int i = 0; i < n; ++i) q.push(a[i] * x);
    while (!q.empty() && remain > 0) {
        int now = q.top();
        q.pop();
        for (int j = k - 1; j >= 0; --j) {
            if (now <= 0) break;
            if (tmp_b[j] <= 0) continue;
            if ((1ll << j) >= now) {
                --tmp_b[j];
                --remain;
                now -= (1ll << j);
            } else {
                int d = min(now / (1ll << j), tmp_b[j]);
                now -= d * (1ll << j);
                tmp_b[j] -= d;
                remain -= d;
            }
            break;
        }
        if (now > 0) q.push(now);
    }
    return q.empty();
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; ++i) cin >> a[i], sum1 += a[i];
        for (int i = 0; i < k; ++i) cin >> b[i], sum2 += b[i] * (1ll << i);
        int l = 0, r = 1 + sum2 / sum1;
        sort(a, a + n);
#ifdef sleepy
        cout << chk(5) << endl;
#endif
#ifndef sleepy
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (chk(mid)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        cout << l << "\n";
#endif
    }
    return 0;
}