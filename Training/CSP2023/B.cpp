#include <bits/stdc++.h>
using i64 = std::int64_t;
using u64 = std::uint64_t;
constexpr u64 BASE = 233;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<u64> p(n + 1);
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = 1LL * p[i - 1] * BASE;
    }

    std::stack<int> st;
    u64 hash = 1;

    std::unordered_map<u64, i64> cnt;
    cnt[1] = 1;
    i64 ans = 0;
    for (auto v : s) {
        int c = v - 'a' + 1;
        if (st.empty()) {
            st.push(c);
            hash += 1ULL * c * p[st.size()];
        } else {
            int top = st.top();
            if (top == c) {
                hash -= 1ULL * c * p[st.size()];
                st.pop();
            } else {
                st.push(c);
                hash += 1ULL * c * p[st.size()];
            }
        }
        ans += cnt[hash];
        cnt[hash] += 1;
    }

    std::cout << ans << std::endl;

    return 0;
}