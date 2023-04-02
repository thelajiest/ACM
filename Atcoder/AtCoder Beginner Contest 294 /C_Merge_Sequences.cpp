#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::map<int, int> idA, idB;

    std::vector<int> comb;
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        idA[x] = i;
        comb.push_back(x);
    }
    for (int i = 1; i <= m; i++) {
        int x;
        std::cin >> x;
        idB[x] = i;
        comb.push_back(x);
    }

    std::sort(begin(comb), end(comb));

    std::vector<int> ansA(n), ansB(m);
    int now = 1;
    for (auto it : comb) {
        if (idA.find(it) != idA.end()) {
            ansA[idA[it] - 1] = now++;
        } else
            ansB[idB[it] - 1] = now++;
    }

    for (auto p : ansA) std::cout << p << " ";
    std::cout << std::endl;
    for (auto p : ansB) std::cout << p << " ";

    return 0;
}