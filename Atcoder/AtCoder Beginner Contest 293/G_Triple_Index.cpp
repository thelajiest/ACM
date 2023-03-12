#include <bits/stdc++.h>

using i64 = std::int64_t;
constexpr int block = 10000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::vector<std::tuple<int, int, int>> query(q);

    for (int i = 0; i < q; i++) {
        auto& [l, r, _] = query[i];
        std::cin >> l >> r;
        l--, r--;
        _ = i;
    }

    std::sort(query.begin(), query.end(), [&](auto a, auto b) {
        auto [l1, r1, id1] = a;
        auto [l2, r2, id2] = b;
        return l1 / block == l2 / block ? r1 < r2 : l1 / block < l2 / block;
    });

    int SZ = *(std::max_element(begin(a), end(a)));
    std::vector<int> cnt(SZ + 1);
    std::vector<i64> ans(q);

    int nowl = 0, nowr = 0;
    cnt[a[0]]++;

    i64 cur = 0;
    for (auto [l, r, id] : query) {
        auto f = [&](int x) -> i64 { return 1LL * x * (x - 1) / 2; };
        while (nowr < r) {
            cur += f(cnt[a[nowr + 1]]);
            cnt[a[nowr + 1]]++;
            nowr++;
        }
        while (nowl > l) {
            cur += f(cnt[a[nowl - 1]]);
            cnt[a[nowl - 1]]++;
            nowl--;
        }
        while (nowr > r) {
            cnt[a[nowr]]--;
            cur -= f(cnt[a[nowr]]);
            nowr--;
        }
        while (nowl < l) {
            cnt[a[nowl]]--;
            cur -= f(cnt[a[nowl]]);
            nowl++;
        }
        ans[id] = cur;
    }

    for (int i = 0; i < q; i++) std::cout << ans[i] << '\n';
    return 0;
}