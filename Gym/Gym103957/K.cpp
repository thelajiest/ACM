#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

using T = double;
struct p3 {
    T x, y, z;
    // Basic vector operations
    p3 operator+(p3 p) { return {x + p.x, y + p.y, z + p.z}; }
    p3 operator-(p3 p) { return {x - p.x, y - p.y, z - p.z}; }
    p3 operator*(T d) { return {x * d, y * d, z * d}; }
    p3 operator/(T d) { return {x / d, y / d, z / d}; }  // only for floating
    bool operator==(p3 p) { return tie(x, y, z) == tie(p.x, p.y, p.z); }
    bool operator!=(p3 p) { return !operator==(p); }
};
T operator|(p3 v, p3 w) { return v.x * w.x + v.y * w.y + v.z * w.z; }
T sq(p3 v) { return v | v; }
double abs(p3 v) { return sqrt(sq(v)); }
p3 unit(p3 v) { return v / abs(v); }
double angle(p3 v, p3 w) {
    double cosTheta = (v | w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}
p3 operator*(p3 v, p3 w) {
    return {v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z,
            v.x * w.y - v.y * w.x};
}
T orient(p3 p, p3 q, p3 r, p3 s) { return (q - p) * (r - p) | (s - p); }

struct plane {
    p3 n;
    T d;
    // From normal n and offset d
    plane(p3 n, T d) : n(n), d(d) {}
    // From normal n and point P
    plane(p3 n, p3 p) : n(n), d(n | p) {}
    // From three non-collinear points P,Q,R
    plane(p3 p, p3 q, p3 r) : plane((q - p) * (r - p), p) {}
    // Will be defined later:
    // - these work with T = int
    T side(p3 p);
    double dist(p3 p);
    plane translate(p3 t);
    // - these require T = double
    plane shiftUp(double dist);
    p3 proj(p3 p) { return p - n * side(p) / sq(n); }
    p3 refl(p3 p) { return p - n * 2 * side(p) / sq(n); }
};

void solve() {}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}