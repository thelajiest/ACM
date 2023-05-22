#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;

    std::cin >> N >> M;

    std::vector<std::string> s(N);
    for (int i = 0; i < N; i++) std::cin >> s[i];

    std::vector<int> perm(N);
    std::iota(begin(perm), end(perm), 0);

    bool ok = false;
    do {
        std::vector<int> id(N);
        for (int i = 0; i < N; i++) id[perm[i]] = i;
        bool flag = true;
        for (int i = 0; i + 1 < N; i++) {
            int diff = 0;
            for (int j = 0; j < M; j++)
                if (s[id[i]][j] != s[id[i + 1]][j]) diff++;
            if (diff != 1) flag = false;
        }
        ok |= flag;
    } while (std::next_permutation(begin(perm), end(perm)));

    if (ok)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}