#include <bits/stdc++.h>

using i64 = std::int64_t;
const double pi = std::acos(-1);
namespace Geometry {
// using T = i64;
// constexpr T eps = 0;

using T = long double;
constexpr T eps = 1E-7;

bool equal(const T &x, const T &y) { return abs(x - y) <= eps; }
int sgn(T x) { return (x > 0) - (x < 0); }
inline constexpr int type(T x, T y) {
    if (x == 0 and y == 0) return 0;
    if (y < 0 or (y == 0 and x > 0)) return -1;
    return 1;
}
struct Point {
    T x, y;
    constexpr Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    constexpr Point operator+() const noexcept { return *this; }
    constexpr Point operator-() const noexcept { return Point(-x, -y); }
    constexpr Point operator+(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    constexpr Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    constexpr Point &operator+=(const Point &p) {
        return x += p.x, y += p.y, *this;
    }
    constexpr Point &operator-=(const Point &p) {
        return x -= p.x, y -= p.y, *this;
    }
    constexpr T operator*(const Point &p) const { return x * p.x + y * p.y; }
    const Point operator/(T d) const { return Point(x / d, y / d); }
    constexpr Point &operator*=(const T &k) { return x *= k, y *= k, *this; }
    constexpr Point operator*(const T &k) { return Point(x * k, y * k); }
    constexpr bool operator==(const Point &r) const noexcept {
        return r.x == x and r.y == y;
    }
    constexpr bool operator!=(const Point &r) const noexcept {
        return !(*this == r);
    }
    constexpr T cross(const Point &r) const { return x * r.y - y * r.x; }
    constexpr T cross(Point a, Point b) const {
        return (a - *this).cross(b - *this);
    }
    constexpr bool operator<(const Point &r) const {
        return std::pair(x, y) < std::pair(r.x, r.y);
    }

    // 1 : left, 0 : same, -1 : right
    constexpr int toleft(const Point &r) const {
        auto t = cross(r);
        return t > eps ? 1 : t < -eps ? -1 : 0;
    }

    constexpr bool arg_cmp(const Point &r) const {
        int L = type(x, y), R = type(r.x, r.y);
        if (L != R) return L < R;

        T X = x * r.y, Y = r.x * y;
        if (X != Y) return X > Y;
        return x < r.x;
    }
};
bool arg_cmp(const Point &l, const Point &r) { return l.arg_cmp(r); }
std::ostream &operator<<(std::ostream &os, const Point &p) {
    return os << p.x << " " << p.y;
}
std::istream &operator>>(std::istream &is, Point &p) {
    is >> p.x >> p.y;
    return is;
}

struct Line {
    Point a, b;
    Line() = default;
    Line(Point a, Point b) : a(a), b(b) {}
    // ax + by = c
    Line(T A, T B, T C) {
        if (A == 0) {
            a = Point(0, C / B), b = Point(1, C / B);
        } else if (B == 0) {
            a = Point(C / A, 0), b = Point(C / A, 1);
        } else {
            a = Point(0, C / B), b = Point(C / A, 0);
        }
    }
    // 1 : left, 0 : same, -1 : right
    constexpr int toleft(const Point &r) const {
        auto t = (b - a).cross(r - a);
        return t > eps ? 1 : t < -eps ? -1 : 0;
    }

    friend std::ostream &operator<<(std::ostream &os, Line &ls) {
        return os << "{"
                  << "(" << ls.a.x << ", " << ls.a.y << "), (" << ls.b.x << ", "
                  << ls.b.y << ")}";
    }
};
std::istream &operator>>(std::istream &is, Line &p) { return is >> p.a >> p.b; }

struct Segment : Line {
    Segment() = default;
    Segment(Point a, Point b) : Line(a, b) {}
};

std::ostream &operator<<(std::ostream &os, Segment &p) {
    return os << p.a << " to " << p.b;
}
std::istream &operator>>(std::istream &is, Segment &p) {
    is >> p.a >> p.b;
    return is;
}

struct Circle {
    Point p;
    T r;
    Circle() = default;
    Circle(Point p, T r) : p(p), r(r) {}
};

using pt = Point;
using Points = std::vector<pt>;
using Polygon = Points;
T cross(const pt &x, const pt &y) { return x.x * y.y - x.y * y.x; }
T dot(const pt &x, const pt &y) { return x.x * y.x + x.y * y.y; }

T abs2(const pt &x) { return dot(x, x); }

int ccw(const Point &a, Point b, Point c) {
    b = b - a, c = c - a;
    if (cross(b, c) > 0) return +1;    // "COUNTER_CLOCKWISE"
    if (cross(b, c) < 0) return -1;    // "CLOCKWISE"
    if (dot(b, c) < 0) return +2;      // "ONLINE_BACK"
    if (abs2(b) < abs2(c)) return -2;  // "ONLINE_FRONT"
    return 0;                          // "ON_SEGMENT"
}

bool parallel(const Line &a, const Line &b) {
    return (cross(a.b - a.a, b.b - b.a) == 0);
}

bool orthogonal(const Line &a, const Line &b) {
    return (dot(a.a - a.b, b.a - b.b) == 0);
}

bool intersect(const Line &l, const Point &p) {
    return abs(ccw(l.a, l.b, p)) != 1;
}

bool intersect(const Line &l, const Line &m) { return !parallel(l, m); }

bool intersect(const Segment &s, const Point &p) {
    return ccw(s.a, s.b, p) == 0;
}

bool intersect(const Line &l, const Segment &s) {
    return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) <= 0;
}

bool intersect(const Segment &s, const Segment &t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
           ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

T norm(const Point &p) { return p.x * p.x + p.y * p.y; }
Point projection(const Segment &l, const Point &p) {
    T t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}

Point crossPoint(const Line &l, const Line &m) {
    T A = cross(l.b - l.a, m.b - m.a);
    T B = cross(l.b - l.a, l.b - m.a);
    if (A == 0 and B == 0) return m.a;
    return m.a + (m.b - m.a) * (B / A);
}

Point crossPoint(const Segment &l, const Segment &m) {
    return crossPoint(Line(l), Line(m));
}

bool isConvex(const Points &p) {
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        if (ccw(p[(i + n - 1) % n], p[i], p[(i + 1) % n]) == -1) return false;
    }
    return true;
}

Points convexHull(Points p) {
    int n = p.size(), k = 0;
    if (n <= 2) return p;
    std::sort(begin(p), end(p),
              [](pt x, pt y) { return (x.x != y.x ? x.x < y.x : x.y < y.y); });
    Points ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) <= 0)
            --k;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) <= 0)
            --k;
    }
    ch.resize(k - 1);
    return ch;
}

T area2(const Points &p) {
    T res = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        res += cross(p[i], p[i == int(size(p)) - 1 ? 0 : i + 1]);
    }
    return res;
}

enum { _OUT, _ON, _IN };

int containsHullPoint(const Polygon &Q, const Point &p) {
    // Brute Force : O(|Q|)
    bool in = false;
    for (int i = 0; i < Q.size(); i++) {
        Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
        if (a.y > b.y) std::swap(a, b);
        if (a.y <= 0 && 0 < b.y && cross(a, b) < 0) in = !in;
        if (cross(a, b) == 0 && dot(a, b) <= 0) return _ON;
    }
    return in ? _IN : _OUT;
}
}  // namespace Geometry

using namespace Geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<Point> hull(n);
    for (int i = 0; i < n; i++) {
        std::cin >> hull[i];
    }
    hull = convexHull(hull);
    while (q--) {
        Point a, b;
        std::cin >> a >> b;
        auto O = (a + b) / 2;
        T r = sqrt(abs2(a - b)) / 2;
        T min = std::numeric_limits<T>::max() / 2.0;
        if (containsHullPoint(hull, O) != _OUT) {
            min = 0;
        } else {
            for (int i = 0; i < n; i++) {
                Segment seg(hull[i], hull[(i + 1) % n]);
                auto proj = projection(seg, O);
                if (fabs(sqrt(abs2(seg.a - proj)) + sqrt(abs2(seg.b - proj)) -
                         sqrt(abs2(seg.b - seg.a))) < eps) {
                    min = std::min(min, abs2(O - proj));
                }
                min = std::min(min, abs2(O - seg.a));
                min = std::min(min, abs2(O - seg.b));
            }
        }
        T ans = min + r * r / 2;

        std::cout << std::fixed << std::setprecision(10) << ans << '\n';
    }
    return 0;
}