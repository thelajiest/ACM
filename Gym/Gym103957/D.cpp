#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    double A, B;
    cin >> A >> B;
    int a = A * 100;
    int b = B * 100;
    set<int> se = {1, 10, 100, 1000, 10000};
    if (a == b) {
        cout << 0 << '\n';
        return;
    }
    if (a < 5 * b) {
        cout << 0.01 << '\n';
    } else {
        if (se.find(b) != se.end())
            cout << 0.02 << '\n';
        else
            cout << 0.01 << '\n';
    }
    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}