#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<i64> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    for (int i = 1; i < N; i++) {
        i64 s, t;
        std::cin >> s >> t;
        A[i] += A[i - 1] / s * t;
    }

    std::cout << A.back() << std::endl;

    return 0;
}