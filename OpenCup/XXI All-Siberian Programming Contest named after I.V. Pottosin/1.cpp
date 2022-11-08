#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n, m, r, c, s;
    cin >> n >> m >> r >> c >> s;
    bool ok = true;
    if (c - s <= 1 && c + s >= m) ok = false;
    if (r - s <= 1 && r + s >= n) ok = false;
    if (r - s <= 1 && c - s <= 1) ok = false;
    if (c + s >= m && r + s >= n) ok = false;

    if (ok)
        cout << "Barsik\n";
    else
        cout << "Tuzik\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}