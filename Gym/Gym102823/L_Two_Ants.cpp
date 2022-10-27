// copied from someone
// geo makes me unhappy,and I don't know why my solution get Wrong Answer...
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define endl '\n'
const int N = 1e6 + 10, M = N * 2;
const double eps = 1e-8;
int sgn(double d) {
    if (fabs(d) < eps) return 0;
    if (d > 0) return 1;
    return -1;
}
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};
typedef Point Vector;
Vector operator+(Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator*(Vector A, double p) { return Vector(A.x * p, A.x * p); }
Vector operator/(Vector A, double p) { return Vector(A.x / p, A.x / p); }
double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
double Length(Vector A) { return sqrt(A.x * A.x + A.y * A.y); }
double Dist(Vector A, Vector B) {
    double dx = A.x - B.x, dy = A.y - B.y;
    return sqrt(dx * dx + dy * dy);
}
Point getIntersectPoint(Point p1, Point p2, Point p3, Point p4) {
    double a1 = p1.y - p2.y, b1 = p2.x - p1.x, c1 = p1.x * p2.y - p2.x * p1.y;
    double a2 = p3.y - p4.y, b2 = p4.x - p3.x, c2 = p3.x * p4.y - p4.x * p3.y;
    return Point((c1 * b2 - c2 * b1) / (a2 * b1 - a1 * b2),
                 (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1));
}
bool is_segment_intersection(Point p1, Point p2, Point p3, Point p4) {
    if (max(p3.x, p4.x) < min(p1.x, p2.x) || max(p1.x, p2.x) < min(p3.x, p4.x))
        return 0;
    if (max(p3.y, p4.y) < min(p1.y, p2.y) || max(p1.y, p2.y) < min(p3.y, p4.y))
        return 0;
    if (Cross(p1 - p4, p3 - p4) * Cross(p2 - p4, p3 - p4) > 0) return 0;
    if (Cross(p4 - p2, p1 - p2) * Cross(p3 - p2, p1 - p2) > 0) return 0;
    return 1;
}
bool OnSegment(Point p, Point p1, Point p2) {
    return sgn(Cross(p - p1, p2 - p1)) == 0 && sgn(Dot(p - p1, p - p2)) <= 0;
}
bool operator==(Point a, Point b) {
    return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps;
}
bool is_Parallel(Point p1, Point p2, Point p3, Point p4) {
    return sgn(Cross(p1 - p2, p3 - p4)) == 0;
}
int t;
Point w1, w2, b1, b2, Jiao;

void doit(int cas) {
    cout << "Case " << cas << ": ";
    cin >> w1.x >> w1.y >> w2.x >> w2.y;
    cin >> b1.x >> b1.y >> b2.x >> b2.y;
    if (w1 == b1 || w1 == b2 || w2 == b1 || w2 == b2) {
        if (sgn(Cross(b2 - b1, w2 - w1)) == 0)
            cout << 0 << '\n';
        else
            cout << "inf" << '\n';
        return;
    }
    if (is_segment_intersection(b1, b2, w1, w2)) {
        if (OnSegment(b1, w1, w2) || OnSegment(b2, w1, w2))
            cout << "inf" << '\n';
        else if (OnSegment(w1, b1, b2) || OnSegment(w2, b1, b2))
            cout << 0 << '\n';
        else
            cout << 0 << '\n';
        return;
    }
    // 直线共线
    if (sgn(Cross(w1 - b1, w1 - b2)) == 0 &&
        sgn(Cross(w2 - b1, w2 - b2)) == 0) {
        cout << 0 << '\n';
        return;
    }
    if (!is_Parallel(b1, b2, w1, w2)) {
        Jiao = getIntersectPoint(b1, b2, w1, w2);
        if (OnSegment(Jiao, b1, b2) || Jiao == b1 || Jiao == b2) {
            cout << 0 << '\n';
            return;
        } else if (OnSegment(Jiao, w1, w2) || Jiao == w1 || Jiao == w2) {
            cout << "inf" << '\n';
            return;
        }
    }
    if (is_segment_intersection(w1, b1, w2, b2)) {
        swap(w1, w2);
    }
    if (is_Parallel(b1, w1, b2, w2)) {
        cout << "inf" << '\n';
        return;
    }
    Jiao = getIntersectPoint(w1, b1, w2, b2);
    double s1 = Cross(w2 - w1, Jiao - w1), s2 = Cross(w2 - w1, b1 - w1);
    if (s1 * s2 > 0)
        cout << "inf" << '\n';
    else {
        double ans = fabs(s1) / 2.0;
        cout << setiosflags(ios::fixed) << setprecision(8) << ans << '\n';
    }
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    for (int _ = 1; _ <= t; _++) {
        doit(_);
    }
    return 0;
}
