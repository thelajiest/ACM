#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int l, r;
    std::cin >> l >> r;

    std::multiset<int> odd, even;
    for (int i = l; i <= r; i++) {
        if (i & 1)
            odd.insert(i);
        else
            even.insert(i);
    }

    while (true) {
        int o = odd.size();
        int e = even.size();
        if (o == 1 || e == 1) break;

        int oddCnt = -1, evenCnt = -1;
        if (o >= 2) {
            int min = *odd.begin();
            int max = *std::prev(odd.end());
            oddCnt = (min + max) / 2;
        }
        if (e >= 2) {
            int min = *even.begin();
            int max = *std::prev(even.end());
            evenCnt = (min + max) / 2;
        }

        if (evenCnt > oddCnt) {
            even.erase(even.begin());
            even.erase(std::prev(even.end()));
            if (evenCnt & 1) {
                odd.insert(evenCnt);
            } else {
                even.insert(evenCnt);
            }
        } else {
            odd.erase(odd.begin());
            odd.erase(std::prev(odd.end()));
            if (oddCnt & 1) {
                odd.insert(oddCnt);
            } else {
                even.insert(oddCnt);
            }
        }
    }

    if ((odd.size() + even.size()) == 2) {
        std::cout << -1 << std::endl;
    } else {
        if (odd.size()) {
            std::cout << (*odd.begin()) << std::endl;
        } else {
            std::cout << (*even.begin()) << std::endl;
        }
    }

    return 0;
}