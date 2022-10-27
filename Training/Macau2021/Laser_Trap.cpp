#include <bits/stdc++.h>
#define int long long

using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point &p) const {
        if (y * p.y < 0) {
            if (y < 0) return true;
            return false;
        }
        return y * p.x - p.y * x < 0;
    }
};

const int INF = 1e18;
const int MAX_N = 1e6 + 7;
Point pt[MAX_N], pnt[MAX_N << 1];
int cnt[MAX_N << 1];
int T, n;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

bool chk(const Point &p2, const Point &p1) {
    __int128 mul = (p1.y * p2.x - p1.x * p2.y);
    return mul >= 0 && mul * mul <= (__int128)(p1.x * p1.x + p1.y * p1.y) *
                                        (__int128)(p2.x * p2.x + p2.y * p2.y);
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> pt[i].x >> pt[i].y;
            int _gcd = gcd(abs(pt[i].x), abs(pt[i].y));
            pt[i].x /= _gcd;
            pt[i].y /= _gcd;
        }
        sort(pt, pt + n);
        int m = 0;
        for (int i = 0, j; i < n; i = j) {
            j = i;
            while (j < n && pt[j].x == pt[i].x && pt[j].y == pt[i].y) {
                ++j;
            }
            cnt[m] = j - i;
            pnt[m].x = pt[i].x;
            pnt[m].y = pt[i].y;
            ++m;
        }
        for (int i = m; i < m * 2; ++i) {
            pnt[i].x = pnt[i - m].x;
            pnt[i].y = pnt[i - m].y;
            cnt[i] = cnt[i - m];
        }
        int l = 0, r = 0;
        int now = 0, ans = 0;
        while (l < m) {
            while (l <= r && r < l + m && r < m * 2 && chk(pnt[l], pnt[r])) {
                now += cnt[r];
                ++r;
            }
            ans = max(ans, now);
            now -= cnt[l];
            ++l;
        }
        cout << n - ans << "\n";
        for (int i = 0; i < m * 2; ++i) cnt[i] = 0;
    }
    return 0;
}