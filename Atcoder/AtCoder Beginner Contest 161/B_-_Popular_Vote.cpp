#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto&& it : a) cin >> it;
    sort(begin(a), end(a), greater<int>());
    i64 sum = accumulate(begin(a), end(a), 0ll);
    bool ok = true;
    for (int i = 0; i < m; i++) {
        if (4 * m * a[i] < sum) ok = false;
    }

    if (ok)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}