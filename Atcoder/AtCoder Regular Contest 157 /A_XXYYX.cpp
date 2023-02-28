#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, a, b, c, d;
    std::cin >> n >> a >> b >> c >> d;

    n--;

    bool flag = true;
    // flag &= (b <= n - b);
    // flag &= (c <= n - c);
    if (a > 0 && d > 0) flag &= ((b != 0) || (c != 0));
    flag &= (abs(b - c) <= 1);
    if (flag)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}