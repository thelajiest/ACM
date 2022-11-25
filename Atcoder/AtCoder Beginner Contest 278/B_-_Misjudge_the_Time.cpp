#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int, int>> ans;

    for (int i = 0; i <= 23; i++) {
        for (int j = 0; j <= 59; j++) {
            int x = i / 10;
            int xx = i % 10;
            int y = j / 10;
            int yy = j % 10;
            int a = x * 10 + y;
            int b = xx * 10 + yy;
            if (0 <= a && a <= 23 && 0 <= b && b <= 59) ans.emplace_back(a, b);
        }
    }

    sort(begin(ans), end(ans));

    int h, m;
    cin >> h >> m;

    int sz = ans.size();

    for (int i = 0; i < sz; i++) {
        if (ans[i] >= make_pair(h, m)) {
            cout << ans[i].first << " " << ans[i].second;
            return 0;
        }
    }

    cout << ans[0].first << " " << ans[0].second;
    return 0;
}