#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr i64 INF = std::numeric_limits<i64>::max();

template <typename T>
T inv_mod(T x, T m) {
    assert(1 <= m);

    T b = m - 2;
    T res = 1;
    for (; b; b /= 2, x = 1LL * x * x % m) {
        if (b % 2) {
            res = 1LL * res * x % m;
        }
    }
    return res;
}

std::pair<long long, long long> inv_gcd(i64 a, i64 b) {
    a = a % b;
    if (a == 0) return std::make_pair(b, 0LL);

    i64 s = b, t = a;
    i64 m0 = 0, m1 = 1;
    while (t) {
        i64 u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        std::swap(s, t);
        std::swap(m0, m1);
    }

    if (m0 < 0) m0 += b / s;
    return std::make_pair(s, m0);
}
// (rem, mod)
std::pair<i64, i64> crt(const std::vector<i64>& r, const std::vector<i64>& m) {
    assert(r.size() == m.size());
    const int n = r.size();
    i64 r0 = 0, m0 = 1;
    for (int i = 0; i < n; ++i) {
        assert(1 <= m[i]);
        i64 r1 = r[i] % m[i], m1 = m[i];
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return std::make_pair(0LL, 0LL);
            continue;
        }

        i64 g, im;
        std::tie(g, im) = inv_gcd(m0, m1);
        i64 u1 = m1 / g;
        if ((r1 - r0) % g) return std::make_pair(0LL, 0LL);
        i64 x = (r1 - r0) / g % u1 * im % u1;

        r0 += x * m0;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }
    return std::make_pair(r0, m0);
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    while (m--) {
        int sa, ta, sb, tb;
        std::cin >> sa >> ta >> sb >> tb;
        sa--, ta--, sb--, tb--;

        std::vector<int> disa(n, -1), disb(n, -1);
        std::vector<int> va, vb;

        auto bfs = [&](int start, int end, std::vector<int>& dis,
                       std::vector<int>& v) {
            std::queue<int> Q;
            Q.push(start);
            dis[start] = 0;
            std::vector<int> last(n, -1);

            while (!Q.empty()) {
                int u = Q.front();
                Q.pop();
                if (u == end) break;
                for (const auto& v : adj[u]) {
                    if (dis[v] == -1) {
                        dis[v] = dis[u] + 1;
                        Q.push(v);
                        last[v] = u;
                    }
                }
            }
            int p = end;
            v.push_back(p);
            while (p != start) {
                // if (p == -1) break;
                p = last[p];
                v.push_back(p);
            }
        };
        bfs(sa, ta, disa, va);
        bfs(sb, tb, disb, vb);

        std::vector<int> intersection;

        std::map<int, int> mp;
        for (const auto& node : va) mp[node] = 1;
        for (const auto& node : vb)
            if (mp[node]) intersection.push_back(node);

        i64 ans = INF;
        int ansNode = -1;
        for (const auto node : intersection) {
            i64 da = disa[ta];
            i64 db = disb[tb];

            auto CRT = [&](i64 a1, i64 m1, i64 a2, i64 m2) -> i64 {
                std::vector<i64> r{a1, a2};
                std::vector<i64> m{m1, m2};
                auto ans = crt(r, m);
                if (ans == std::make_pair(0LL, 0LL))
                    return INF;
                else
                    return ans.first;
            };

            auto updata = [&](i64 crtResult) {
                if (ans > crtResult) {
                    ans = crtResult;
                    ansNode = node;
                }
                return;
            };
            updata(CRT(disa[node], 2 * da, disb[node], 2 * db));
            updata(CRT(2 * da - disa[node], 2 * da, disb[node], 2 * db));
            updata(CRT(disa[node], 2 * da, 2 * db - disb[node], 2 * db));
            updata(
                CRT(2 * da - disa[node], 2 * da, 2 * db - disb[node], 2 * db));
        }
        if (ansNode == -1)
            std::cout << "-1\n";
        else
            std::cout << ansNode + 1 << '\n';
    }

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