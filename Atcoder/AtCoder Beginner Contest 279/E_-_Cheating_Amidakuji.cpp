#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    cin >> n >> m;

    vector<int> b(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    vector<int> cnt(n + 1);

    for (int i = 1; i <= n; i++) cnt[i] = i;

    vector<array<int, 2>> pos(m + 1);
    for (int i = 1; i <= m; i++) {
        auto& [x, y] = pos[i];
        x = cnt[b[i]];
        y = cnt[b[i] + 1];
        swap(cnt[b[i]], cnt[b[i] + 1]);
    }
    vector<int> P(n + 1);
    for (int i = 1; i <= n; i++) P[cnt[i]] = i;
    for (int i = 1; i <= m; i++) {
        auto [x, y] = pos[i];

        if (x != 1 && y != 1)
            cout << P[1] << '\n';
        else {
            x = max(x, y);
            cout << P[x] << '\n';
        }
    }
    return 0;
}