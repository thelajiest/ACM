#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;

    i64 A, B;

    std::cin >> N >> A >> B;

    std::string s;

    std::cin >> s;
    i64 ans = std::numeric_limits<i64>::max() / 2.0;
    for (int r = 0; r < N; r++) {
        i64 cur = r * A;
        for (int l = 0, r = N - 1; l < r; l++, r--) {
            if (s[l] != s[r]) cur += B;
        }
        ans = std::min(ans, cur);
        std::rotate(s.begin(), s.begin() + 1, s.end());
    }

    std::cout << ans << std::endl;

    return 0;
}