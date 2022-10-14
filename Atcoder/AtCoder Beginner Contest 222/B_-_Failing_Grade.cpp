#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;

    cin >> n >> p;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ans += (x < p);
    }

    cout << ans << endl;

    return 0;
}