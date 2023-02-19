#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    std::string s;
    std::cin >> s;

    for (auto& c : s) {
        if ('A' <= c && c <= 'Z') {
            c -= 'A';
            c += 'a';
        }
    }
    bool flag = true;
    flag &= (s.find("kfc") != std::string::npos);
    flag &= (s.find("crazy") != std::string::npos);
    flag &= (s.find("thursday") != std::string::npos);
    flag &= (s.find("vivo") != std::string::npos);
    flag &= (s.find("50") != std::string::npos);

    if (flag)
        std::cout << "Yes\n";
    else
        std::cout << "No\n";

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}