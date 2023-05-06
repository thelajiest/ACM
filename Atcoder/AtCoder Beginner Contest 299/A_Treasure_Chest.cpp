#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<char> b;
    for (auto p : s) {
        if (p == '|' || p == '*') b.push_back(p);
    }

    if (b == std::vector<char>{'|', '*', '|'})
        std::cout << "in";
    else
        std::cout << "out";

    return 0;
}