#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s1, s2;
    std::cin >> s1 >> s2;

    int a = s1[0] - s1[1];
    int b = s2[0] - s2[1];

    std::cout << ((abs(a) == abs(b)) ? "Yes" : "No") << std::endl;

    return 0;
}