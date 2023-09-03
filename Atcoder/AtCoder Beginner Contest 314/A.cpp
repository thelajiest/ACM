#include <bits/stdc++.h>

using i64 = std::int64_t;

const std::string pi =
    "14159265358979323846264338327950288419716939937510582097494459230781640628"
    "62089986280348253421170679";
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::cout << "3." + std::string{pi.begin(), pi.begin() + n};

    return 0;
}