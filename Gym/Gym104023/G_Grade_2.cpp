#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 x, n;
    cin >> x >> n;

    i64 LG = __lg(x);
    i64 round = 1LL << (LG + 1);
    i64 roundans = 0;
    vector<i64> cnt(round);
    for (i64 i = 0; i < round; i++) {
        if (std::gcd(i * x ^ x, x) == 1) roundans++;
        cnt[i] = roundans;
    }

    auto f = [&](i64 bound) -> i64 {
        i64 sum = 0;
        i64 now = 0;
        sum += (bound / round) * roundans;
        sum += cnt[bound % round];
        return sum;
    };
    while (n--) {
        i64 l, r;
        cin >> l >> r;
        cout << f(r) - f(l - 1) << '\n';
    }
    return 0;
}