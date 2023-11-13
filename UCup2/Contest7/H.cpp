#include <bits/stdc++.h>
using i64 = std::int64_t;

std::vector<int> prime_sieve(int N) {
    std::vector<bool> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    std::vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> cnt(10);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cnt[x] = 1;
    }

    auto prime = prime_sieve(1E7);

    for (auto p : prime) {
        bool flag = false;
        auto t = p;
        while (p) {
            if (cnt[p % 10]) flag = true;
            p /= 10;
        }

        if (flag) continue;
        std::cout << t << std::endl;
        return 0;
    }

    std::cout << -1 << std::endl;
    return 0;
}