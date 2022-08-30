#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef vector<int> VI;
typedef pair<int, int> pii;
constexpr double eps = 1e-10;
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
    friend T cross(P a, P b) { return a.x * b.y - a.y * b.x; }
    friend T dot(P a, P b) { return a.x * b.x + a.y * b.y; }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

using P = Point<double>;
struct Line {
    P a, b;
    Line() {}
    Line(P _a, P _b) : a(_a), b(_b) {}
};

int sideof(const P& s, const P& e, const P& p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}

int sideof(P y, const Line x) { return sideof(x.a, x.b, y, eps); }

pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0)  // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

P lineInter(Line a, Line b) { return lineInter(a.a, a.b, b.a, b.b).second; }
vector<P> halfp(std::vector<Line> lines) {
    // template copied from jiangly & KACTL
    auto sgn = [&](P a) -> int {
        return (a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1);
    };
    std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        ;
        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }
        return cross(d1, d2) > 0;
    });

    std::deque<Line> ls;
    std::deque<P> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }

        while (!ps.empty() && sideof(ps.back(), l) < 1) {
            ps.pop_back();
            ls.pop_back();
        }

        while (!ps.empty() && sideof(ps[0], l) < 1) {
            ps.pop_front();
            ls.pop_front();
        }

        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                if (sideof(ls.back().a, l) < 1) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }

        ps.push_back(lineInter(ls.back(), l));
        ls.push_back(l);
    }

    while (!ps.empty() && sideof(ps.back(), ls[0]) < 1) {
        ps.pop_back();
        ls.pop_back();
    }
    if (ls.size() <= 2) {
        return {};
    }
    ps.push_back(lineInter(ls[0], ls.back()));

    return vector<P>(ps.begin(), ps.end());
}
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
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

    int _;
    cin >> _;
    while (_--) {
        int n;
        double h;
        cin >> n >> h;
        double w;
        cin >> w;
        vector<P> a(n);
        vector<Line> hull;
        for (auto&& [x, y] : a) cin >> x >> y;

        for (int i = 0; i < n; i++) {
            P now(a[(i + 1) % n] - a[i]);
            now = now.normal() * w;
            hull.emplace_back(a[i] + now, a[(i + 1) % n] + now);
        }

        a = halfp(hull);
        cout << fixed << setprecision(10);
        double lx, ly, lz;
        cin >> lx >> ly >> lz;
        P light{lx, ly};
        auto inside = inPolygon(a, light, false);
        if (!inside) {
            double pz = lz / (lz - h);
            if (pz < 0) {
                cout << 0 << '\n';
                continue;
            }
            for (int i = 0; i < a.size(); i++) {
                P s = light + (a[i] - light) * pz;
                P e = light + (a[(i + 1) % (a.size())] - light) * pz;
                hull.emplace_back(s, e);
            }

            a = halfp(hull);
        }
        double sum = 0;
        for (int i = 0; i < a.size(); i++)
            sum += cross(a[i], a[(i + 1) % a.size()]) / 2.0;
        cout << sum << '\n';
    }
}