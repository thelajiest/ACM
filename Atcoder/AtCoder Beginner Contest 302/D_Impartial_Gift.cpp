#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    i64 D;
    std::cin >> N >> M >> D;

    std::vector<i64> A(N), B(M);

    for (int i = 0; i < N; i++) std::cin >> A[i];
    for (int i = 0; i < M; i++) std::cin >> B[i];

    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end(), std::greater());

    i64 ans = -1;
    for (int i = 0; i < N; i++) {
        auto pos =
            std::lower_bound(B.begin(), B.end(), A[i] + D, std::greater());
        if (pos == B.end()) continue;
        if (std::abs(A[i] - (*pos)) <= D) ans = std::max(ans, A[i] + (*pos));
    }

    std::cout << ans << std::endl;

    return 0;
}