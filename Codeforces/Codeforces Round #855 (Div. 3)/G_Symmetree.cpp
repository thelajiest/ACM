#include <bits/stdc++.h>

using i64 = std::int64_t;
using u64 = std::uint64_t;

u64 f(u64 x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
    return x;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<u64> hsh(n);
    std::mt19937_64 mrand(
        std::chrono::steady_clock::now().time_since_epoch().count());

    const u64 c = std::uniform_int_distribution<u64>(
        0, std::numeric_limits<u64>::max())(mrand);
    const u64 RANDOM = std::uniform_int_distribution<u64>(
        0, std::numeric_limits<u64>::max())(mrand);

    auto dfsHash = [&](auto&& self, int u, int fa) -> void {
        hsh[u] = c;
        for (const auto& v : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
            hsh[u] += f(hsh[v] ^ RANDOM);
        }
    };

    dfsHash(dfsHash, 0, -1);

    auto checkDfs = [&](auto&& self, int u, int fa) -> bool {
        std::map<u64, std::vector<int>> mp;
        for (const auto& v : adj[u]) {
            if (v == fa) continue;
            mp[hsh[v]].push_back(v);
        }
        std::vector<int> line;
        int need = 0;
        for (auto [hshValue, lt] : mp) {
            if (lt.size() % 2 == 1) {
                std::copy(lt.begin(), lt.end(), std::back_inserter(line));
                need++;
            }
        }
        if (need >= 2) return false;

        bool flag = (line.size() == 0);
        for (const auto& v : line) {
            flag |= self(self, v, u);
        }
        return flag;
    };

    if (checkDfs(checkDfs, 0, -1))
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

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