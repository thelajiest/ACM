# Solution for AtCoder Beginner Contest 286

今年的年味确实不浓，很无聊，于是打打AtCoder防止智力下降。

[题目链接](https://atcoder.jp/contests/abc286)

## A - Range Swap

有个东西叫`std::swap_ranges`，直接用就行了。

## B - Cat

直接模拟即可。

## C - Rotate and Palindrome

枚举位移距离，然后暴力算就行了。$\mathcal{O}(N^2)$

```cpp
i64 ans = std::numeric_limits<i64>::max() / 2.0;
for (int r = 0; r < N; r++) {
  i64 cur = r * A;
  for (int l = 0, r = N - 1; l < r; l++, r--) {
    if (s[l] != s[r]) cur += B;
  }
  ans = std::min(ans, cur);
  std::rotate(s.begin(), s.begin() + 1, s.end());
}

std::cout << ans << std::endl;
```

## D - Money in Hand

似乎是个裸的背包，$\mathcal{O}(NXB)$跑一遍就行。

```cpp
#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x;
    std::cin >> n >> x;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(x + 1));

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int a, b;

        std::cin >> a >> b;

        for (int j = 0; j <= x; j++) {
            for (int t = 0; t <= b; t++) {
                if (j + a * t > x) continue;
                dp[i][j + a * t] |= dp[i - 1][j];
            }
        }
    }

    int ans = 0;

    for (int i = 0; i <= n; i++) {
        ans |= dp[i][x];
    }

    if (ans) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}
```

## E - Souvenir

数据范围比较小，可以用[Floyd-Warshall algorithm](https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html)，点权可以叠加到边权上，合并时减去重复计算的就行。时间复杂度：$\mathcal{O}(N^3)$。

```cpp
#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr i64 INF = std::numeric_limits<i64>::max() / 3.0;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    std::cin >> n;

    std::vector<i64> val(n);

    for (int i = 0; i < n; i++) std::cin >> val[i];

    std::vector<std::vector<i64>> mp(n, std::vector<i64>(n, INF));
    std::vector<std::vector<i64>> cost(n, std::vector<i64>(n, 0));

    for (int i = 0; i < n; i++) {
        std::string in;
        std::cin >> in;
        for (int j = 0; j < n; j++) {
            if (in[j] == 'Y') mp[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (i != j) cost[i][j] = val[i] + val[j];
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mp[i][k] + mp[k][j] < mp[i][j]) {
                    mp[i][j] = mp[i][k] + mp[k][j];
                    cost[i][j] = cost[i][k] + cost[k][j] - val[k];
                } else if (mp[i][k] + mp[k][j] == mp[i][j]) {
                    cost[i][j] =
                        std::max(cost[i][j], cost[i][k] + cost[k][j] - val[k]);
                }
            }
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        if (mp[u][v] >= INF)
            std::cout << "Impossible\n";
        else
            std::cout << mp[u][v] << " " << cost[u][v] << '\n';
    }

    return 0;
}
```

## F - Guess The Number 2

是个中国剩余定理题。

考虑将$i\rightarrow A_i$的函数关系建造一个有向图，构造若干个环，环长为$m_1,m_2,...,m_t$，则$\sum_{i=1}^t m_i =M$。

函数复合相当于给定起点在环内循环，则$N$次后可以对每个环的每个位置算出相对偏移，即$t$个同余方程$N \equiv r_i\mod m_i$。直接CRT即可。

但是要保证$M$不能超过$110$，且$LCM(\{m_i\})\leq 10^9$，不然可能答案不唯一。

笔者选择了：$4, 5, 7, 9, 11, 13, 17, 19, 23$。

```cpp
#include <bits/stdc++.h>

using i64 = std::int64_t;

template <typename T>
constexpr T safe_mod(T x, T m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}
template <typename T>
constexpr std::pair<T, T> inv_gcd(T a, T b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    T s = b, t = a;
    T m0 = 0, m1 = 1;
    while (t) {
        T u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

template <typename T>
T inv_mod(T x, T m) {
    assert(1 <= m);
    auto z = inv_gcd(x, m);
    assert(z.first == 1);
    return z.second;
}

template <typename T>
std::pair<T, T> crt(const std::vector<T>& r, const std::vector<T>& m) {
    assert(r.size() == m.size());
    int n = int(r.size());
    // Contracts: 0 <= r0 < m0
    T r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(1 <= m[i]);
        T r1 = safe_mod(r[i], m[i]), m1 = m[i];
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        auto [g, im] = inv_gcd(m0, m1);
        T u1 = (m1 / g);
        if ((r1 - r0) % g) return {0, 0};
        T x = (r1 - r0) / g % u1 * im % u1;
        r0 += x * m0;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> p = {4, 5, 7, 9, 11, 13, 17, 19, 23};

    int M = 108;

    std::cout << M << std::endl;
    std::cout.flush();

    std::vector<int> to(M + 1);
    int np = 1;
    for (int i = 0; i < static_cast<int>(p.size()); i++) {
        int cur = p[i];
        int fn = np;
        for (int j = 1; j <= cur; j++) {
            if (j != cur)
                to[np] = j + fn;
            else
                to[np] = fn;
            np++;
        }
    }

    for (int i = 1; i <= M; i++) {
        std::cout << to[i] << " ";
    }
    std::cout << std::endl;
    std::cout.flush();

    std::vector<int> ans(M + 1);
    for (int i = 1; i <= M; i++) {
        std::cin >> ans[i];
    }

    std::vector<int> res;

    for (int i = 0, fs = 1; i < static_cast<int>(p.size()); i++) {
        int diff = ((ans[fs] - fs) % p[i] + p[i]) % p[i];
        res.push_back(diff);
        fs += p[i];
    }

    auto [rem, mod] = crt<int>(res, p);

    std::cout << rem << std::endl;

    return 0;
}
```

## G - Unique Walk

这个题看上去就很欧拉回路。

考虑对不在$S$集合的边构造子图$G$，该子图肯定是若干个联通块。联通块内的必经一次的边可以不用考虑，因为联通块内任意两点都可以经过非$S$内的边到达，因此可以调整使得联通块内的$S$内的边仅经过一次。

由于联通块内部无影响，可以缩点建立新图，并且新图之间的边都在$S$内。显然充要条件为新图是半欧拉图（奇数度数的点有且仅有2个或0个）。

时间复杂度：$\mathcal{O}(N)$

```cpp
#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;

    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);

    std::vector<std::pair<int, int>> E(m);

    for (auto& [u, v] : E) {
        std::cin >> u >> v;
        u--, v--;
    }

    int k;
    std::cin >> k;

    std::vector<int> sig(m);
    for (int i = 0; i < k; i++) {
        int x;
        std::cin >> x;
        x--;
        sig[x] = 1;
    }

    for (int i = 0; i < m; i++) {
        if (!sig[i]) {
            auto [u, v] = E[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    std::vector<int> col(n, -1);

    int p = 0;
    for (int i = 0; i < n; i++) {
        if (col[i] == -1) {
            auto dfs = [&](auto&& self, int u) -> void {
                col[u] = p;
                for (const auto& v : adj[u]) {
                    if (col[v] == -1) self(self, v);
                }
            };
            dfs(dfs, i);
            p++;
        }
    }

    std::vector<int> deg(p);
    for (int i = 0; i < m; i++) {
        if (sig[i]) {
            auto [u, v] = E[i];
            deg[col[u]]++;
            deg[col[v]]++;
        }
    }

    int h = 0;
    for (int i = 0; i < p; i++) {
        h += (deg[i] % 2);
    }

    if (h == 2 || h == 0)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}
```

## Ex - Don't Swim

神秘计算几何。

似乎就是个计算几何模版+最短路。

考虑建图，凸包上的点和S，T连边，需要写一个线段和凸包判交来剔除不合法的边。然后直接跑Dijkstra算法即可。

时间复杂度：$\mathcal{O}(N\log N)$。

当然有一些线性做法，不过笔者选择拒绝思考，抄了KACTL计算几何模版。

```cpp
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
```

