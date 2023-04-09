#include <bits/stdc++.h>

using i64 = std::int64_t;
using i128 = __int128_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 N, M;
    std::cin >> N >> M;

    if (i128(N) * N < M) {
        std::cout << -1 << std::endl;
        return 0;
    }

    i64 ansx = -1, mx = std::numeric_limits<i64>::max() / 3.0;
    for (i64 x = 1; (i128(x) * x <= 4 * M) && x <= N; x++) {
        i128 ret = (i128)x * ((M + x - 1) / x);
        if (((M + x - 1) / x) > N) continue;
        if (ret >= M) {
            mx = std::min<i128>(mx, ret);
        }
    }

    std::cout << mx;
    return 0;
}