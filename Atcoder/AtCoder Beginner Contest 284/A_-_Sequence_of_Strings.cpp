#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    std::cin >> n;

    std::vector<std::string> a(n);

    for (auto&& it : a) std::cin >> it;

    for (auto it = a.rbegin(); it != a.rend(); it++) {
        std::cout << *it << '\n';
    }

    return 0;
}