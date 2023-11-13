#include <bits/stdc++.h>
using i64 = std::int64_t;

struct Point {
    double x, y;
    friend bool operator<(const Point& a, const Point& b) {
        return std::make_pair(a.x, a.y) < std::make_pair(b.x, b.y);
    }
};

Point midPoint(const Point& a, const Point& b) {
    return Point{(a.x + b.x) / 2, (a.y + b.y) / 2};
}
struct Rect {
    Point a, b;
};

double area(const Rect& rect) {
    return (rect.b.x - rect.a.x) * (rect.b.y - rect.a.y);
}
double unionTwoRect(const Rect& A, const Rect& B) {
    double ret = 0.0;
    Point LL{std::max(A.a.x, B.a.x), std::max(A.a.y, B.a.y)};
    Point UR{std::min(A.b.x, B.b.x), std::min(A.b.y, B.b.y)};
    if ((LL.x <= UR.x) && (LL.y <= UR.y)) {
        ret = area(Rect{LL, UR});
    }
    return ret;
}

template <class T>
struct Flow {
    const int n;
    struct Edge {
        int to;
        T cap;
        Edge(int to, T cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}

    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int& i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T maxFlow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
};
void solve() {
    int m, n;
    std::cin >> m >> n;

    std::vector<Rect> G(m);
    std::vector<Rect> D(n);

    std::map<Point, std::vector<int>> mpG, mpD;
    for (int i = 0; i < m; i++) {
        double x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        G[i] = {{x1, y1}, {x2, y2}};
        auto mP = midPoint(G[i].a, G[i].b);
        mpG[mP].push_back(i);
        // std::cerr << area(G[i]);
    }

    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        D[i] = {{x1, y1}, {x2, y2}};
        auto mP = midPoint(D[i].a, D[i].b);
        mpD[mP].push_back(i);
    }

    /*
    0 - m-1 G
    m - n+m-1 D
    S : n + m
    T : n + m + 1
    */
    int S = n + m, T = n + m + 1;
    Flow<i64> flow(n + m + 2);
    for (int i = 0; i < m; i++) {
        flow.addEdge(S, i, 1);
    }

    for (int i = m; i < n + m; i++) {
        flow.addEdge(i, T, 1);
    }

    for (int i = 0; i < m; i++) {
        auto mP = midPoint(G[i].a, G[i].b);
        for (double dx = -2; dx <= 2; dx += 0.5) {
            for (double dy = -2; dy <= 2; dy += 0.5) {
                Point cur{mP.x + dx, mP.y + dy};
                for (const auto& pd : mpD[cur]) {
                    auto ua = unionTwoRect(D[pd], G[i]);
                    if (ua * 2 >= area(G[i])) {
                        flow.addEdge(i, pd + n, 1);
                    }
                }
            }
        }
    }

    std::cout << flow.maxFlow(S, T) << '\n';

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}