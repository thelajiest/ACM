#include <bits/stdc++.h>

using i64 = std::int64_t;

std::vector<int> zFunction(const std::string& s) {
    int n = (int)s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        } else {
            z[i] = std::max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

std::pair<i64, i64> get(const std::string& s, const std::string& t) {
    int n = s.size(), m = t.size();

    std::vector cnt(m, std::vector(m, 0LL));

    std::string st = t + s;
    for (int i = 0; i < m; i++) {
        auto z = zFunction({st.begin() + i, st.end()});
        for (int j = m; j < n + m; j++) {
            if (z[j - i] == 0) continue;
            cnt[i][i] += 1;
            if (std::min(i + z[j - i] - 1, m - 1) + 1 < m)
                cnt[i][std::min(i + z[j - i] - 1, m - 1) + 1] -= 1;
        }
    }

    i64 ret = 0;
    for (int i = 0; i < m; i++) {
        ret += cnt[i][0];
        for (int j = 1; j < m; j++) {
            cnt[i][j] += cnt[i][j - 1];
            ret += cnt[i][j];
        }
    }

    std::vector d(m, std::vector(m, 0LL));
    for (int j = 0; j < m; j++) {
        d[0][j] = cnt[0][j];
        for (int i = 1; i <= j; i++) {
            d[i][j] = d[i - 1][j] + cnt[i][j];
        }
    }

    auto sum = [&](int l, int r, int k) -> i64 {
        // cnt[l][k] ... cnt[r][k]
        if (l == 0) return d[r][k];
        return d[r][k] - d[l - 1][k];
    };
    std::vector lcp(m, std::vector(m, 0));
    for (int i = 0; i < m; i++) {
        auto z = zFunction({t.begin() + i, t.end()});
        for (int j = i; j < m; j++) {
            lcp[i][j] = z[j - i];
        }
    }

    i64 ans = 0;

    for (int i = 0; i < m; i++) {
        for (int j = i + 2; j < m; j++) {
            ans += sum(i + 1, std::min(i + lcp[i][j], j - 1), j - 1);
        }
    }
    return {ans, ret};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    std::cin >> s >> t;

    auto [ans1, eq1] = get(s, t);
    auto [ans2, eq2] = get(t, s);
    assert(eq1 == eq2);

    std::cout << ans1 + ans2 + eq1 << std::endl;

    return 0;
}