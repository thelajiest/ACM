#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

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
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
template <class P>
bool online(const P& a, const P& b, const P& p) {
    return (b - a).cross(p - a) == 0;
}
template <class P>
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
template <class P>
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
    return {s.begin(), s.end()};
}
mt19937_64 rng(time(0));
void solve() {
    int n;
    cin >> n;

    using point = Point<double>;

    vector<point> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }

    int TryTimes = max(100, 10 * n);
    auto myrand = [&](i64 a, i64 b) -> i64 {
        return uniform_int_distribution<i64>(a, b)(rng);
    };
    if (n < 5) {
        cout << "NO\n";
        return;
    }
    for (int _ = 1; _ <= TryTimes; _++) {
        int i1 = myrand(0, n - 1);
        int i2 = myrand(0, n - 1);
        while (i2 == i1) i2 = myrand(0, n - 1);
        int i3 = myrand(0, n - 1);
        while (i3 == i1 || i3 == i2) i3 = myrand(0, n - 1);
        int i4 = myrand(0, n - 1);
        while (i4 == i1 || i4 == i2 || i4 == i3) i4 = myrand(0, n - 1);
        int i5 = myrand(0, n - 1);
        while (i5 == i1 || i5 == i2 || i5 == i3 || i5 == i4)
            i5 = myrand(0, n - 1);
        bool flag = true;
        if (online(a[i1], a[i2], a[i3]) && online(a[i1], a[i2], a[i4]) &&
            online(a[i1], a[i2], a[i5]))
            continue;
        else {
            vector<point> now = {a[i1], a[i2], a[i3], a[i4], a[i5]};
            for (int i = 0; i < 5; i++) {
                auto zx = now[i];
                vector<point> res;
                for (int j = 0; j < 5; j++) {
                    if (i == j) continue;
                    res.push_back(now[j]);
                }
                bool flag = true;
                for (int k1 = 0; k1 < 4; k1++) {
                    for (int k2 = 0; k2 < k1; k2++) {
                        auto inter = segInter(zx, res[k1], zx, res[k2]);
                        if (inter.size() != 1 || !(inter[0] == zx))
                            flag = false;
                    }
                }
                if (flag) {
                    cout << "YES\n";
                    cout << (int)zx.x << " " << (int)zx.y << '\n';
                    for (auto [x, y] : res) {
                        cout << (int)x << " " << (int)y << '\n';
                    }
                    return;
                }
            }
        }
    }
    cout << "NO\n";
    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}