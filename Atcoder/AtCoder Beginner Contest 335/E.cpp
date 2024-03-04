#include <bits/stdc++.h>
using i64 = std::int64_t;
constexpr int INF = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::vector<std::vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<int> dis(N, INF);
    dis[0] = 0;

    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>>
        Q;

    Q.push({A[0], 0, 0});

    std::vector<int> vis(N, 0);

    while (!Q.empty()) {
        auto [a, w, u] = Q.top();
        Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (const auto v : adj[u]) {
            if (A[v] < A[u]) {
                dis[v] = std::min(dis[v], INF);
            } else {
                if (A[v] == A[u])
                    dis[v] = std::min(dis[v], dis[u]);
                else
                    dis[v] = std::min(dis[v], dis[u] - 1);
            }
            Q.push({A[v], dis[v], v});
        }
    }

    if (dis[N - 1] > 0)
        std::cout << 0 << std::endl;
    else
        std::cout << -dis[N - 1] + 1 << std::endl;

    return 0;
}