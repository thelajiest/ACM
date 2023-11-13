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

struct Point {
    int x, y;

    Point() { x = y = 0; }
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
};

int dist(int x, int y) { return x * x + y * y; }

int cross(const Point &a, const Point &b) { return a.x * b.y - b.x * a.y; }

const int INF = 4e18;

int T, n;

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        vector<Point> ps(n, Point());
        for (int i = 0; i < n; i++) {
            cin >> ps[i].x >> ps[i].y;
        }
        vector<vector<int>> dia(n, vector<int>(n, 0)),
            rdia(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dia[i][j] = dist((ps[i].x - ps[(i + j) % n].x),
                                 (ps[i].y - ps[(i + j) % n].y));
                rdia[i][j] = dist((ps[i].x - ps[(i - j + n) % n].x),
                                  (ps[i].y - ps[(i - j + n) % n].y));
                if (j) {
                    dia[i][j] = max(dia[i][j], dia[i][j - 1]);
                    rdia[i][j] = max(rdia[i][j], rdia[i][j - 1]);
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < n; i++) {
            vector<int> lft(n, 0), rgt(n, 0);
            for (int j = 0; j < n; j++) {
                int p = (i + j) % n;
                rgt[j] = rdia[p][j];
                if (j) {
                    rgt[j] = max(rgt[j], rgt[j - 1]);
                }
                p = (i - j + n) % n;
                lft[j] = dia[p][j];
                if (j) {
                    lft[j] = max(lft[j], lft[j - 1]);
                }
            }
            int st1 = 2, st2 = 2;
            while (st1 < n && cross(ps[i] - ps[(i + 1) % n],
                                    ps[i] - ps[(i + st1) % n]) == 0) {
                ++st1;
            }
            while (st2 < n && cross(ps[i] - ps[(i - 1 + n) % n],
                                    ps[i] - ps[(i - st2 + n) % n]) == 0) {
                ++st2;
            }
            for (int j = st1; j <= n - st2; j++) {
                ans = min(ans, rgt[j] + lft[n - j]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}