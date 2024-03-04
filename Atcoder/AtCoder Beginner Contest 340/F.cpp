#include <bits/stdc++.h>
using i64 = std::int64_t;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    auto res = exgcd(b, a % b, x, y);
    i64 t = x;
    x = y;
    y = t - a / b * y;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 X, Y;
    std::cin >> X >> Y;

    std::swap(X, Y);
    i64 A = 0, B = 0;

    auto d = exgcd(abs(X), abs(Y), A, B);
    if (X < 0) A = -A;
    if (Y > 0) B = -B;

    if (2 % d != 0) {
        std::cout << "-1" << std::endl;
    } else {
        A = A * (2 / d);
        B = B * (2 / d);
        std::cout << A << " " << B << std::endl;
    }
    return 0;
}