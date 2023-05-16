#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string a, b;

    std::cin >> a >> b;

    std::vector<int> mp1(26), mp2(26);
    int cnt1 = 0, cnt2 = 0;

    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] == '@')
            cnt1++;
        else
            mp1[a[i] - 'a']++;
    }

    for (int i = 0; i < (int)b.size(); i++) {
        if (b[i] == '@')
            cnt2++;
        else
            mp2[b[i] - 'a']++;
    }

    int nd1 = 0, nd2 = 0;
    std::set<int> no;
    for (int i = 0; i < 26; i++) no.insert(i);

    for (auto c : {'a', 't', 'c', 'o', 'd', 'e', 'r'}) {
        int i = c - 'a';
        no.erase(i);
        if (mp1[i] > mp2[i]) {
            nd1 += mp1[i] - mp2[i];
        }
        if (mp1[i] < mp2[i]) {
            nd2 += mp2[i] - mp1[i];
        }
    }

    for (auto i : no) {
        if (mp1[i] != mp2[i]) {
            std::cout << "No" << std::endl;
            return 0;
        }
    }

    if (cnt1 + cnt2 >= nd1 + nd2)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}