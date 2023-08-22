#include <bits/stdc++.h>

using i128 = __int128_t;

i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    auto res = exgcd(b, a % b, x, y);
    i128 t = x;
    x = y;
    y = t - a / b * y;
    return res;
}

template <typename T, typename U>
T ceil(T x, U y) {
    return (x > 0 ? (x + y - 1) / y : x / y);
}
template <typename T, typename U>
T floor(T x, U y) {
    return (x > 0 ? x / y : (x - y + 1) / y);
}

template <class T>
void read(T &x) {
    long long f;
    std::cin >> f;
    x = f;
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i128 n;
    i128 a, b, c;
    i128 X;

    read(n);
    read(a), read(b), read(c), read(X);
    i128 g = std::gcd((long long)b, (long long)c);

    b /= g, c /= g;

    i128 x, y;
    i128 ans = 0;

    for (int i = 1; i <= n; i++) {
        i128 k = X - 1LL * a * i;
        if (k < 0) continue;
        if (k % g != 0) continue;
        k /= g;
        exgcd(b, c, x, y);

        i128 x0 = x * k, y0 = y * k;
        /*
            bx0 + cy0 = k
            x = x0 + k * c
            y = y0 - k * b
            1 <= x0 + k * c <= n
            1 <= y0 - k * b <= n
        */

        i128 up = std::min(floor(n - x0, c), floor(y0 - 1, b));
        i128 down = std::max(ceil(1 - x0, c), ceil(y0 - n, b));

        ans += std::max<i128>(0LL, up - down + 1);
    }

    std::cout << (long long)ans << std::endl;

    return 0;
}