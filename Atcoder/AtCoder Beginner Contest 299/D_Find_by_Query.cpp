#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int L = 1, R = n;

    while (L < R) {
        int mid = (L + R + 1) / 2;
        std::cout << "? " << mid << std::endl;
        int x;
        std::cin >> x;
        if (x == 0)
            L = mid;
        else
            R = mid - 1;
    }

    std::cout << "! " << L << std::endl;
    return 0;
}