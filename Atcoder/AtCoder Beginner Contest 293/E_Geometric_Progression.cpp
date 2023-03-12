#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 a, x, m;
    std::cin >> a >> x >> m;

    using mat = std::array<std::array<i64, 2>, 2>;
    mat D = {std::array<i64, 2>{a, 1}, std::array<i64, 2>{0, 1}};

    auto mul = [&](const mat& A, const mat& B) -> mat {
        mat ret = {std::array<i64, 2>{0, 0}, std::array<i64, 2>{0, 0}};
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) {
                    ret[i][j] = (ret[i][j] + A[i][k] * B[k][j] % m) % m;
                }
        return ret;
    };

    auto power = [&](mat a, i64 b) -> mat {
        mat res = {std::array<i64, 2>{1, 0}, std::array<i64, 2>{0, 1}};
        for (; b; b /= 2, a = mul(a, a)) {
            if (b % 2) {
                res = mul(res, a);
            }
        }
        return res;
    };

    D = power(D, x);

    std::cout << D[0][1] << std::endl;
    return 0;
}