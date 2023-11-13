#include <bits/stdc++.h>

using i64 = std::int64_t;

constexpr double INF = std::numeric_limits<double>::max() / 3.0;
template <class T>
struct Point3D {
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(R p) const { return tie(x, y, z) < tie(p.x, p.y, p.z); }
    bool operator==(R p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }
    P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }

    T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(R p) const {
        return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    // Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
    double phi() const { return atan2(y, x); }
    // Zenith angle (latitude) to the z-axis in interval [0, pi]
    double theta() const { return atan2(sqrt(x * x + y * y), z); }
    P unit() const { return *this / (T)dist(); }  // makes dist()=1
    // returns unit vector normal to *this and p
    P normal(P p) const { return cross(p).unit(); }
    // returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
    }
};
using P = Point3D<double>;

constexpr double EPS = 1E-11;

bool parallel(P& a, P& b) {
    auto c = a.cross(b);
    return c.dist() < EPS;
}

P projection(const P& l, const P& p) {
    double t = p.dot(l) / l.dist2();
    return l * t;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<P> a(n);
    for (auto& v : a) {
        std::cin >> v.x >> v.y >> v.z;
    }

    double ans = INF;
    for (int k1 = 0; k1 < n; k1++) {
        for (int k2 = 0; k2 < n; k2++) {
            for (int t1 = 0; t1 < n; t1++) {
                for (int t2 = 0; t2 < n; t2++) {
                    if (k1 == k2 || t1 == t2) continue;
                    P v1 = a[k1] - a[k2];
                    P v2 = a[t1] - a[t2];
                    if (parallel(v1, v2)) continue;
                    auto v = v1.cross(v2);

                    double min = INF;
                    double max = 0;
                    for (int x = 0; x < n; x++) {
                        auto p1 = projection(v, a[x]);
                        auto d = p1.dist();
                        if (p1.dot(v) < 0) d = -d;
                        min = std::min(min, d);
                        max = std::max(max, d);
                    }
                    ans = std::min(ans, max - min);
                }
            }
        }
    }

    std::cout << std::fixed << std::setprecision(14);
    if (ans < INF)
        std::cout << ans << std::endl;
    else
        std::cout << 0 << std::endl;
    return 0;
}