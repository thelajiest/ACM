#include <bits/stdc++.h>
using i64 = std::int64_t;
using u64 = std::uint64_t;

constexpr u64 FIXED_RANDOM = 10;
constexpr double phi = 0.77351;
inline u64 shift(u64 x) {
    x ^= FIXED_RANDOM;
    return x ^ (x >> 16);
}

inline int NDE(int hash) { return (1ULL << hash) / phi; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    int x, y;

    if (q == 2) {
        std::cin >> x >> y;
    }
    std::vector<u64> a(n);

    if (q == 1) {
        int hash = 0;
        u64 xval = 0;
        std::set<u64> se;
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
            hash = std::max(hash, __builtin_ctzll(shift(a[i])));
            xval ^= a[i];
            if (se.find(a[i]) != se.end()) {
                se.erase(se.find(a[i]));
            } else
                se.insert(a[i]);
        }

        if (se.size() == 2) {
            std::cout << *se.begin() << " " << *(std::next(se.begin()))
                      << std::endl;
        } else {
            std::cout << hash << " " << xval << std::endl;
        }
    } else {
        int hash = x;
        u64 xval = y;
        std::set<u64> se;
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
            hash = std::max(hash, __builtin_ctzll(shift(a[i])));
            xval ^= a[i];
            if (se.find(a[i]) != se.end()) {
                se.erase(se.find(a[i]));
            } else
                se.insert(a[i]);
        }
    }

    return 0;
}