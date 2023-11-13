#include <bits/stdc++.h>

using i64 = std::int64_t;

struct Point {
    i64 x, y;
    constexpr i64 cross(const Point &r) const { return x * r.y - y * r.x; }
    constexpr Point operator-() const noexcept { return Point(-x, -y); }
    constexpr Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Point> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i].x >> h[i].y;
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        int a = ((i - 1) + n) % n;
        int b = i;
        int c = (i + 1) % n;

        /*
           a      c
            \    /
             \  /
              \/
              b
        */
        int t = i;
        while (h[i].y == h[t].y) t = (t + 1) % n;
        if (h[b].y < h[a].y && h[b].y < h[t].y) {
            if (h[c].y != h[b].y) {
                Point p = h[b] - h[a];
                Point q = h[c] - h[b];
                if (p.cross(q) > 0) {
                    ans++;
                }
            } else {
                if (h[c].x > h[b].x) ans++;
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}
