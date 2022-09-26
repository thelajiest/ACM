#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> xp(n + 1);

    for (int i = 1; i <= n; i++) {
        auto& [x, y] = xp[i];
        cin >> x >> y;
    }
    vector<int> f(n + 1);
    function<int(int)> find = [&](int x) -> int {
        if (f[x] == x)
            return x;
        else
            f[x] = find(f[x]);
        return f[x];
    };
    auto merge = [&](int x, int y) {
        int _x = find(x);
        int _y = find(y);
        if (_x == _y) return;
        f[_x] = _y;
        return;
    };
    for (int i = 1; i <= n; i++) f[i] = i;

    for (int i = 1; i <= n; i++) {
        auto [x, y] = xp[i];

        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx - dy) > 1) continue;
                for (int j = 1; j <= n; j++) {
                    auto [xx, yy] = xp[j];
                    if (xx == dx + x && yy == dy + y) merge(i, j);
                }
            }
    }
    set<int> se;
    for (int i = 1; i <= n; i++) {
        int _f = find(i);
        se.insert(_f);
    }

    cout << se.size();

    return 0;
}