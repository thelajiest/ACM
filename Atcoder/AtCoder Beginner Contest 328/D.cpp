#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    std::vector<char> st;

    for (auto& c : s) {
        if (st.size() < 2) {
            st.push_back(c);
        } else {
            int size = std::size(st);
            if (st[size - 2] == 'A' && st[size - 1] == 'B' && c == 'C') {
                st.resize(size - 2);
            } else {
                st.push_back(c);
            }
        }
    }

    for (auto& c : st) std::cout << c;
    std::cout << std::endl;

    return 0;
}