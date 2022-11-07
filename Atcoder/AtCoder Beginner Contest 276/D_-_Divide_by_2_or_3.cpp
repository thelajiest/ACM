#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<tuple<int, int, int>> a(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int cnt2(0), cnt3(0);
        while (x % 2 == 0) {
            x /= 2;
            cnt2++;
        }
        while (x % 3 == 0) {
            x /= 3;
            cnt3++;
        }
        a[i] = {x, cnt2, cnt3};
    }
    bool ok = true;
    auto [x, cnt2, cnt3] = a[0];
    for (int i = 1; i < n; i++) {
        auto [nowx, c2, c3] = a[i];
        if (nowx != x) ok = false;
        cnt2 = min(cnt2, c2);
        cnt3 = min(cnt3, c3);
    }
    if (!ok) {
        cout << "-1";
    } else {
        i64 ans = 0;
        for (auto [nowx, c2, c3] : a) {
            ans += c2 - cnt2 + c3 - cnt3;
        }
        cout << ans;
    }

    return 0;
}