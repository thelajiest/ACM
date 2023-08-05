#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<std::string> p = {"ACE", "BDF", "CEG", "DFA", "EGB", "FAC", "GBD"};

    std::string _;
    std::cin >> _;

    if (p.find(_) != p.end())
        std::cout << "Yes\n";
    else
        std::cout << "No\n";

    return 0;
}