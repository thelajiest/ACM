#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        if (x % 2 == 1) ans++;
    }

    std::cout << ans << '\n';

    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;

    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}