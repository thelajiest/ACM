#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::vector<char> s(n);
    std::vector<int> o2(n, -1), o3(n, -1);
    std::cin >> n;

    std::string _;
    std::cin >> _;
    s = {begin(_), end(_)};

    std::cin >> q;
    for (int i = 0; i < q; i++) {
        int t, x;
        char c;
        std::cin >> t >> x >> c;
        x--;
        if (t == 1) {
            s[x] = c;
        }
        if (t == 2) {
            o2[x] = i;
        }
        if (t == 3) {
            o3[x] = i;
        }
    }

    auto Up = [&](char a) {
        if (std::islower(a)) a = a - 'a' + 'A';
        return a;
    };
    auto Low = [&](char a) {
        if (std::isupper(a)) a = a - 'A' + 'a';
        return a;
    };

    for (int i = 0; i < n; i++) {
        if (o2[i] == -1 && o3[i] == -1) std::cout << s[i];
        if (o2[i] == -1 && o3[i] != -1) std::cout << Up(s[i]);
        if (o2[i] != -1 && o3[i] == -1) std::cout << Low(s[i]);
        if (o2[i] != -1 && o2[i] != -1) {
            if (o2[i] > o3[i])
                std::cout << Low(s[i]);
            else
                std::cout << Up(s[i]);
        }
    }

    return 0;
}