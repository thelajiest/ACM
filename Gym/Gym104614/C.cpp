#include <bits/stdc++.h>

using i64 = std::int64_t;

using i128 = __uint128_t;
int main() {
    std::cin.tie(nullptr);

    i64 n;
    std::cin >> n;

    std::vector<i128> a(n);
    std::vector<i128> cnt(100);
    std::vector<i128> cnt2(100);

    for (i128 i = 0; i < n; i++) {
        char c;
        std::cin >> c;
        if ('0' <= c && c <= '9') a[i] = c - '0';
        if (c == 'T') a[i] = 10;
        if (c == 'J') a[i] = 11;
        if (c == 'Q') a[i] = 12;
        if (c == 'K') a[i] = 13;
        if (c == 'A') a[i] = 1;
        cnt[a[i]]++;
        cnt2[a[i] <= 9 ? a[i] : 10]++;
    }

    auto b = a;
    std::sort(begin(b), end(b));
    b.resize(std::unique(begin(b), end(b)) - begin(b));

    std::vector<std::vector<i128>> c15;

    std::vector<std::vector<std::pair<i128, i128>>> d15;
    std::vector<i128> cur;
    auto dfs = [&](auto&& self, i128 x, i128 res) -> void {
        if (res == 0) {
            c15.push_back(cur);
        }
        for (i128 i = x; i <= res; i++) {
            cur.push_back(i);
            self(self, i, res - i);
            cur.pop_back();
        }
    };
    dfs(dfs, 1, 15);

    for (auto& l : c15) {
        std::vector<std::pair<i128, i128>> cur;
        std::sort(begin(l), end(l));
        i128 t = l.size();
        for (i128 i = 0, j; i < t; i = j) {
            j = i;
            while (j < t && l[i] == l[j]) j++;
            cur.emplace_back(l[i], j - i);
        }
        d15.emplace_back(cur);
    }

    auto C = [&](i128 n, i128 m) -> i128 {
        if (n < 0 || m < 0 || n < m) return 0;
        i128 ret = 1;

        for (i128 i = n; i >= n - m + 1; i--) ret *= (i128)i;
        for (i128 i = 1; i <= m; i++) ret /= (i128)i;
        return ret;
    };

    i128 ans = 0;
    for (auto curL : d15) {
        i128 curAns = 1;
        for (auto [x, len] : curL) {
            curAns *= C(cnt2[x], len);
        }
        ans += (i128)(2) * curAns;
    }

    for (i128 i = 0; i < 100; i++) {
        ans += (i128)(2) * C(cnt[i], 2);
    }

    std::vector<std::vector<i128>> order;
    for (i128 i = 0, j; i < (i128)b.size(); i = j) {
        j = i;
        while (j < (i128)b.size() && b[j] == b[i] + j - i) j++;
        order.push_back({b.begin() + i, b.begin() + j});
    }

    for (auto curL : order) {
        i128 curAns = 1;
        i128 t = curL.size();
        if (curL.size() < 3) continue;
        for (i128 j = 0; j < curL.size(); j++) curAns *= cnt[curL[j]];
        ans += curAns * t;
    }

    auto trans = [&](i128 x) -> std::string {
        std::string s;
        while (x) {
            s += char((x % 10) + '0');
            x /= 10;
        }
        std::reverse(begin(s), end(s));
        return s;
    };
    std::cout << trans(ans) << std::endl;
    return 0;
}