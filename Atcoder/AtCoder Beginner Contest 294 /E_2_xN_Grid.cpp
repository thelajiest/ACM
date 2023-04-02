#include <bits/stdc++.h>

using i64 = std::int64_t;
using namespace std;
struct Interval {
    i64 start, end;
    bool type;  // 0 for L-type, 1 for R-type
    Interval(i64 s, i64 e, bool t) : start(s), end(e), type(t) {}
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 L, n, m;
    std::cin >> L >> n >> m;

    std::vector<std::pair<i64, i64>> a(n), b(m);
    for (auto& [l, r] : a) std::cin >> l >> r;
    for (auto& [l, r] : b) std::cin >> l >> r;

    std::map<i64, std::vector<Interval>> mp;

    i64 l = 1;
    for (auto [num, len] : a) {
        i64 r = l + len - 1;
        mp[num].emplace_back(l, r, 1);
        l = r + 1;
    }
    l = 1;
    for (auto [num, len] : b) {
        i64 r = l + len - 1;
        mp[num].emplace_back(l, r, 0);
        std::cerr << l << " " << r << std::endl;
        l = r + 1;
    }

    i64 ans = 0;

    for (auto& [col, intervals] : mp) {
        sort(intervals.begin(), intervals.end(),
             [](const Interval& a, const Interval& b) {
                 return a.start == b.start ? a.type > b.type
                                           : a.start < b.start;
             });
        i64 cnt1 = 0, cnt2 = 0;
        for (const Interval& interval : intervals) {
            if (!interval.type) {
                if (cnt2 > 0)
                    ans +=
                        std::max(0LL, min(interval.end, cnt2) - interval.start);
                cnt1 += interval.end - interval.start;
            } else {
                if (cnt1 > 0)
                    ans +=
                        std::max(0LL, min(interval.end, cnt1) - interval.start);
                cnt2 += interval.end - interval.start;
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}