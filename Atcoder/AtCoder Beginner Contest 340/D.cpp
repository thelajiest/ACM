#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<std::vector<std::pair<int, i64>>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        i64 A, B;
        int X;
        std::cin >> A >> B >> X;
        X--;
        adj[i].emplace_back(i + 1, A);
        adj[i].emplace_back(X, B);
    }

    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>,
                        std::greater<std::pair<i64, int>>>
        Q;

    std::vector<i64> dis(N, 1E18);
    std::vector<int> vis(N);

    Q.push({0, 0});
    dis[0] = 0;
    while (!Q.empty()) {
        auto [d, x] = Q.top();
        Q.pop();
        if (vis[x]) continue;
        vis[x] = 1;

        for (auto [y, w] : adj[x]) {
            if (dis[x] + w < dis[y]) {
                dis[y] = dis[x] + w;
                Q.push({dis[y], y});
            }
        }
    }

    std::cout << dis.back() << std::endl;
    return 0;
}