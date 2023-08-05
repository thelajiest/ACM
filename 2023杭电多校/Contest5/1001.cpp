#include <bits/stdc++.h>

using namespace std;
constexpr long double EPS = 1E-12;
using i64 = std::int64_t;
template <typename T, typename D = long double>
struct pt {
    static_assert(is_floating_point_v<D>);
    T x = 0, y = 0;

    pt() = default;
    template <typename T1, typename T2>
    pt(T1 a, T2 b) : x(a), y(b) {}
    template <typename U>
    pt(const pt<U>& p) : x(p.x), y(p.y) {}

    pt<T> operator+(const pt& p) const { return {x + p.x, y + p.y}; }
    pt<T> operator-(const pt& p) const { return {x - p.x, y - p.y}; }
    pt<T> operator*(const T c) const { return {x * c, y * c}; }
    pt<T> operator/(const T c) const { return {x / c, y / c}; }
    pt<T> operator-() const { return {-x, -y}; }

    pt<T>& operator+=(const pt& p) {
        x += p.x, y += p.y;
        return *this;
    }
    pt<T>& operator-=(const pt& p) {
        x -= p.x, y -= p.y;
        return *this;
    }
    pt<T>& operator*=(const T c) {
        x *= c, y *= c;
        return *this;
    }
    pt<T>& operator/=(const T c) {
        x /= c, y /= c;
        return *this;
    }

    template <typename U>
    bool operator==(const pt<U>& p) const {
        if constexpr (is_integral_v<T> && is_integral_v<U>)
            return p.x == x && p.y == y;
        return abs(p.x - x) < EPS && abs(p.y - y) < EPS;
    }
    template <typename U>
    bool operator!=(const pt<U>& p) const {
        return !(*this == p);
    }
    template <typename U>
    bool operator<(const pt<U>& p) const {
        if constexpr (is_integral_v<T> && is_integral_v<U>)
            return x < p.x || (x == p.x && y < p.y);
        return x + EPS < p.x || (abs(x - p.x) < EPS && y + EPS < p.y);
    }

    template <typename U>
    auto dot(const pt<U>& p) const {
        return x * p.x + y * p.y;
    }
    template <typename U>
    auto cross(const pt<U>& p) const {
        return x * p.y - y * p.x;
    }
    template <typename U>
    D dist(const pt<U>& p) const {
        return hypotl(x - p.x, y - p.y);
    }
    template <typename U>
    auto dist2(const pt<U>& p) const {
        return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    }
    template <typename U>
    auto mdist(const pt<U>& p) const {
        return abs(x - p.x) + abs(y - p.y);
    }

    template <typename U>
    friend auto dot(const pt& p1, const pt<U>& p2) {
        return p1.x * p2.x + p1.y * p2.y;
    }
    template <typename U>
    friend auto cross(const pt& p1, const pt<U>& p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
    template <typename U>
    friend D dist(const pt& p1, const pt<U>& p2) {
        return hypotl(p1.x - p2.x, p1.y - p2.y);
    }
    template <typename U>
    friend auto dist2(const pt& p1, const pt<U>& p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }
    template <typename U>
    friend auto mdist(const pt& p1, const pt<U>& p2) {
        return abs(p1.x - p2.x) + abs(p1.y - p2.y);
    }

    void self_rotate_about_origin(D ang) {
        const D sn = sinl(ang), cs = cosl(ang);
        D nx = x * cs - sn * y;
        D ny = x * sn + cs * y;
        x = nx, y = ny;
    }

    void self_normalize() {
        if (abs(x) < EPS && abs(y) < EPS) assert(0);
        D c = hypotl(x, y);
        x /= c, y /= c;
    }

    pt<D> get_normalized() const {
        if (abs(x) < EPS && abs(y) < EPS) assert(0);
        D c = hypotl(x, y);
        return pt(x / c, y / c);
    }

    friend istream& operator>>(istream& is, pt& p) { return is >> p.x >> p.y; }
    friend ostream& operator<<(ostream& os, const pt& p) {
        return os << '{' << p.x << ", " << p.y << '}';
    }
};
template <typename T>
bool is_point_on_ray(const pt<T>& p, const pt<T>& p1, const pt<T>& p2) {
    return abs(cross(p - p1, p - p2)) < EPS && dot(p2 - p1, p - p1) > -EPS;
}

template <typename T = long double, typename D = long double>
struct line {
    static_assert(is_floating_point_v<D>);
    T A, B, C;

    line() = default;
    template <typename T1, typename T2, typename T3>
    line(T1 A, T2 B, T3 C) : A(A), B(B), C(C) {
        self_normalize();
    }
    template <typename U1, typename U2>
    line(const pt<U1>& a, const pt<U2>& b)
        : A(a.y - b.y), B(b.x - a.x), C(cross(a, b)) {
        self_normalize();
    }
    template <typename U>
    line(const line<U>& l) : A(l.A), B(l.B), C(l.C) {
        self_normalize();
    }

    template <typename U>
    auto eval(const pt<U>& p) const {
        return A * p.x + B * p.y + C;
    }

    template <typename U>
    D get_dist_to_pt(const pt<U>& p) const {
        if constexpr (is_integral_v<T>) {
            return abs(A * p.x + B * p.y + C) / hypotl(A, B);
        } else {
            return abs(A * p.x + B * p.y + C);
        }
    }

    void self_normalize() {
        if constexpr (is_integral_v<T>) {
            assert(A || B);
            T gc = __gcd(__gcd(abs(A), abs(B)), abs(C));
            if (A < 0 || (A == 0 && B < 0)) gc *= -1;
            A /= gc, B /= gc, C /= gc;
        } else {
            assert(abs(A) + abs(B) > EPS);
            D u = hypotl(A, B);
            if (A < -EPS || (abs(A) < EPS && B < -EPS)) u *= -1;
            A /= u, B /= u, C /= u;
        }
    }

    template <typename U>
    line get_normal_from_point(const pt<U>& p) const {
        return line(p, p + pt<T>(A, B));
    }

    template <typename U>
    void make_normal_from_point(const pt<U>& p) {
        *this = line(p, p + pt<T>(A, B));
    }

    template <typename U>
    pt<D> get_projection_of_point(const pt<U>& p) const {
        pt<D> norm{A, B};
        norm.self_normalize();
        norm *= get_dist_to_pt(p);
        pt<D> o(p);
        o += norm;
        if (get_dist_to_pt(o) < EPS) return o;
        o -= norm * 2;
        assert(get_dist_to_pt(o) < EPS);
        return o;
    }

    template <typename U>
    pt<D> intersect(const line<U>& l) const {
        assert(!is_equal_to(l));
        D x = (D)(l.C * B - C * l.B) / (A * l.B - l.A * B);
        D y = (D)(l.A * C - A * l.C) / (A * l.B - l.A * B);
        return {x, y};
    }

    template <typename U>
    bool is_parallel_to(const line<U>& l) const {
        if constexpr (is_integral_v<T> && is_integral_v<U>)
            return l.A == A && l.B == B;
        return abs(l.A - A) + abs(l.B - B) < EPS;
    }

    template <typename U>
    bool is_equal_to(const line<U>& l) const {
        if constexpr (is_integral_v<T> && is_integral_v<U>)
            return l.A == A && l.B == B && l.C == C;
        return abs(l.A - A) + abs(l.B - B) + abs(l.C - C) < EPS;
    }

    void print_kxb() const {
        if (abs(B) < EPS) {
            cout << "x = " << -((D)C / A) << '\n';
        } else {
            cout << "y = " << -((D)A / B) << "x + " << -((D)C / B) << '\n';
        }
    }

    void print_abc() const {
        cout << A << "x + " << B << "y + " << C << " = 0\n";
    }
};
template <typename T>
bool is_point_on_segment(const pt<T>& p, const pt<T>& p1, const pt<T>& p2) {
    return abs(cross(p - p1, p - p2)) < EPS && dot(p2 - p1, p - p1) > -EPS &&
           dot(p1 - p2, p - p2) > -EPS;
}
template <typename T>
T dist_point_segment(const pt<T>& p, const pt<T>& p1, const pt<T>& p2) {
    if (p1 == p2) {
        return dist(p, p1);
    }
    line l = line(p1, p2);
    pt i = l.get_projection_of_point(p);
    return is_point_on_segment(i, p1, p2) ? dist(p, i)
                                          : min(dist(p, p1), dist(p, p2));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m, n;
    std::cin >> m >> n;

    using Point = pt<long double>;
    std::vector<Point> t(m), s(n);
    for (auto& it : t) std::cin >> it.x >> it.y;
    for (auto& it : s) std::cin >> it.x >> it.y;

    for (int j = 0; j < n; j++) {
        const auto& v = s[j];
        long double ans = std::numeric_limits<long double>::max();
        for (int i = 0; i + 1 < m; i++) {
            ans = std::min(ans, dist_point_segment(v, t[i + 1], t[i]));
        }
        for (int i = m - 1; i >= 1; i--) {
            ans = std::min(ans, dist_point_segment(v, t[i], t[i - 1]));
        }

        if (ans < 1E-6) ans = 0;
        std::cout << std::fixed << std::setprecision(4) << ans << "\n";
    }
    return 0;
}