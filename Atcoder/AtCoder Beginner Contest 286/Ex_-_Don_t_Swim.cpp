#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr double INF = std::numeric_limits<double>::max() / 3.0;
template <class T>
int sgn(T x) {
    return (x > 0) - (x < 0);
}
template <class T = double>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return std::tie(x, y) < std::tie(p.x, p.y); }
    bool operator==(P p) const { return std::tie(x, y) == std::tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }  // makes dist()=1
    P perp() const { return P(-y, x); }        // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
};
#define cmp(i, j) sgn(dir.perp().cross(poly[(i) % n] - poly[(j) % n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P>
int extrVertex(std::vector<P>& poly, P dir) {
    int n = size(poly), lo = 0, hi = n;
    if (extr(0)) return 0;
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if (extr(m)) return m;
        int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
        (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
    }
    return lo;
}
template <class P>
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
template <class P>
std::vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c),
         od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    std::set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {s.begin(), s.end()};
}
#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
bool lineHull(P a, P b, std::vector<P>& poly) {
    int endA = extrVertex(poly, (a - b).perp());
    int endB = extrVertex(poly, (b - a).perp());
    if (cmpL(endA) < 0 || cmpL(endB) > 0) return true;
    std::array<int, 2> res;
    for (int i = 0; i < 2; i++) {
        int lo = endB, hi = endA, n = size(poly);
        while ((lo + 1) % n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmpL(m) == cmpL(endB) ? lo : hi) = m;
        }
        res[i] = (lo + !cmpL(hi)) % n;
        std::swap(endA, endB);
    }
    std::array<int, 2> ans = res;
    if (res[0] == res[1]) return true;
    if (!cmpL(res[0]) && !cmpL(res[1]))
        switch ((res[0] - res[1] + size(poly) + 1) % size(poly)) {
            case 0:
                ans = std::array<int, 2>{res[0], res[0]};
            case 2:
                ans = std::array<int, 2>{res[1], res[1]};
        }
    auto [f1, f2] = res;
    if (f1 == -1 || f2 == -1) return true;
    int sz1 = segInter(a, b, poly[f1], poly[(f1 + 1) % poly.size()]).size();
    int sz2 = segInter(a, b, poly[f2], poly[(f2 + 1) % poly.size()]).size();
    if (sz1 == 1 && sz2 == 1) return false;
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    std::cin >> n;

    std::vector<Point<double>> hull(n);

    for (auto& [x, y] : hull) std::cin >> x >> y;

    Point s, t;
    std::cin >> s.x >> s.y >> t.x >> t.y;

    int cnt = n + 2;

    std::vector<std::vector<std::pair<int, double>>> adj(cnt);

    auto Dist = [](const Point<double>& a, const Point<double>& b) -> double {
        double rx = a.x - b.x;
        double ry = a.y - b.y;
        return std::sqrt(rx * rx + ry * ry);
    };

    for (int i = 0; i < n; i++) {
        double curDist = Dist(hull[i], hull[(i + 1) % n]);
        adj[i].emplace_back((i + 1) % n, curDist);
        adj[(i + 1) % n].emplace_back(i, curDist);
    }

    for (int i = 0; i < n; i++) {
        if (!lineHull(s, hull[i], hull)) continue;
        double curDist = Dist(s, hull[i]);
        adj[n].emplace_back(i, curDist);
        adj[i].emplace_back(n, curDist);
    }

    for (int i = 0; i < n; i++) {
        if (!lineHull(t, hull[i], hull)) continue;
        double curDist = Dist(t, hull[i]);
        adj[n + 1].emplace_back(i, curDist);
        adj[i].emplace_back(n + 1, curDist);
    }

    if (lineHull(s, t, hull)) {
        double curDist = Dist(s, t);
        adj[n + 1].emplace_back(n, curDist);
        adj[n].emplace_back(n + 1, curDist);
    }

    std::vector<double> dis(cnt, INF);
    std::vector<int> vis(cnt);
    dis[n] = 0;
    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        std::greater<std::pair<double, int>>>
        Q;
    Q.push({0, n});
    while (!Q.empty()) {
        auto [uw, u] = Q.top();
        Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                Q.push({dis[v], v});
            }
        }
    }

    std::cout << std::fixed << std::setprecision(10) << dis[n + 1];
    return 0;
}