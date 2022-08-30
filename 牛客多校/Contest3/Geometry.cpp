#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef vector<int> VI;
typedef pair<int, int> pii;

template <class T>
int sgn(T x) {
    return (x > 0) - (x < 0);
}
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T operator*(P p) const { return x * p.x + y * p.y; }
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
    T friend cross(P a, P b) { return a.x * b.y - a.y * b.x; }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
typedef Point<double> P;
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c),
         od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {(s).begin(), (s).end()};
}
bool inPolygon(vector<P>& p, P a, bool strict = true) {
    int cnt = 0, n = (p).size();
    for (int i = 0; i < n; i++) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a)) return !strict;
        // or: if (segDist(p[i], q, a) <= eps) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<P> a(n);
    for (auto& [x, y] : a) cin >> x >> y;
    int m;
    cin >> m;
    vector<P> b(m);
    for (auto& [x, y] : b) cin >> x >> y;

    P v1, v2;
    cin >> v1.x >> v1.y >> v2.x >> v2.y;
    auto v = v2 - v1;
    double dis = v.dist();
    v = v.unit() * 1e60;
    constexpr double eps = 1e-10;
    auto Minkowski_Sum = [&](const vector<P>& a, const vector<P>& b) {
        vector<P> res;
        auto sgnp = [&](P a) -> int {
            return (a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1);
        };
        auto argcmp = [&](P a, P b) {
            return sgnp(a) != sgnp(b) ? sgnp(a) == 1 : a.cross(b) > eps;
        };
        vector<pair<P, P>> e1(a.size()), e2(b.size()),
            edge(a.size() + b.size());
        auto cmp = [&](const pair<P, P>& u, const pair<P, P>& v) {
            return argcmp(u.second - u.first, v.second - v.first);
        };
        for (size_t i = 0; i < a.size(); i++)
            e1[i] = {a[i], a[(i + 1) % a.size()]};
        for (size_t i = 0; i < b.size(); i++)
            e2[i] = {b[i], b[(i + 1) % b.size()]};
        rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
        rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
        merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
        const auto check = [&](const vector<P>& res, const P& u) {
            const auto back1 = res.back(), back2 = *prev(res.end(), 2);
            return sgn<double>((back1 - back2).cross(u - back1)) == 0 &&
                   (back1 - back2) * (u - back1) > -eps;
        };
        auto u = e1[0].first + e2[0].first;
        for (auto& v : edge) {
            while (res.size() > 1 && check(res, u)) res.pop_back();
            res.push_back(u);
            u = u + v.second - v.first;
        }
        if (res.size() > 1 && check(res, res[0])) res.pop_back();
        return res;
    };

    for (auto& it : b) it = P(-it.x, -it.y);
    auto hull = Minkowski_Sum(a, b);
    if (inPolygon(hull, P(0, 0), false)) {
        cout << 0;
        return 0;
    }
    double ans = 1e20;
    for (int i = 0; i < hull.size(); i++) {
        auto inter = segInter(P(0, 0), v, hull[i], hull[(i + 1) % hull.size()]);
        if (inter.size() == 0) continue;
        for (auto p : inter) {
            ans = min(ans, p.dist());
        }
    }
    if (ans >= 1e19) {
        cout << -1;
    } else {
        if (ans == 0)
            cout << 0;
        else
            cout << fixed << setprecision(10) << ans / dis;
    }
    return 0;
}
