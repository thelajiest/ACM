#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 2E6 + 100;

int gcd(int u, int v) { return v ? gcd(v, u % v) : u; }

int lcm(int u, int v) { return u * v / gcd(u, v); }

int T;
int a, b, c, d, v, t;
int n;
int w[MAX_N];

void cal(int x, int y) {
    // 计算 [0, lcm(x, y)) 中的倍数列表
    n = 0;
    int r = lcm(x, y);
    int p = 0, q = 0;
    while (p <= r && q <= r) {
        if (p == q) {
            w[n++] = p;
            p += x;
            q += y;
        } else if (p > q) {
            w[n++] = q;
            q += y;
        } else if (p < q) {
            w[n++] = p;
            p += x;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> a >> b >> c >> d >> v >> t;
        cal(a, c);
        int p = 0;
        for (int i = 1; i < n; ++i) {
            if (w[i] - w[i - 1] > v) p += 1;
        }

        int r = lcm(a, c);
        int ans = b + d + t / a * b + t / c * d - t / r * p;
        for (int i = 1; w[i] <= t % r; ++i) {
            if (w[i] - w[i - 1] > v) ans -= 1;
        }
        ans -= 1;             // 开头必灭
        ans = max(ans, 0ll);  // 丁丁情况
        cout << ans << '\n';
    }

    return 0;
}