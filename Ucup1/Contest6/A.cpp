#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::map<char, std::vector<std::string>> mp;
    mp['F'] = {"UUU", "UUC"};
    mp['L'] = {"UUA", "UUG", "CUU", "CUC", "CUA", "CUG"};

    mp['I'] = {"AUU", "AUC", "AUA"};

    mp['M'] = {"AUG"};

    mp['V'] = {"GUU", "GUC", "GUA", "GUG"};

    mp['S'] = {"UCU", "UCC", "UCA", "UCG", "AGU", "AGC"};

    mp['P'] = {"CCU", "CCC", "CCA", "CCG"};

    mp['T'] = {"ACU", "ACC", "ACA", "ACG"};

    mp['A'] = {"GCU", "GCC", "GCA", "GCG"};

    mp['Y'] = {"UAU", "UAC"};
    mp['H'] = {"CAU", "CAC"};
    mp['Q'] = {"CAA", "CAG"};
    mp['N'] = {"AAU", "AAC"};
    mp['K'] = {"AAA", "AAG"};
    mp['D'] = {"GAU", "GAC"};
    mp['E'] = {"GAA", "GAG"};
    mp['C'] = {"UGU", "UGC"};
    mp['W'] = {"UGG"};
    mp['R'] = {"CGU", "CGC", "CGA", "CGG", "AGA", "AGG"};
    mp['G'] = {"GGU", "GGC", "GGA", "GGG"};
    mp['B'] = {"UAA", "UAG", "UGA"};

    std::map<std::string, char> mp2;
    for (auto [c, _] : mp) {
        for (auto s : _) mp2[s] = c;
    }

    int T;
    std::cin >> T;
    while (T--) {
        std::string s;
        std::cin >> s;
        int n = s.size();

        std::string ans;
        for (int i = 0; i < n; i += 3) {
            std::string cur = {s.begin() + i, s.begin() + i + 3};
            if (mp2[cur] == 'B') break;
            ans += mp2[cur];
        }
        std::cout << ans << '\n';
    }

    return 0;
}