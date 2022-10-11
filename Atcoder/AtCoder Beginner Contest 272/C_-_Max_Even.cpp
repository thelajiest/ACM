#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<i64> odd, even;

    for (int i = 0; i < n; i++) {
        i64 x;
        cin >> x;
        if (x % 2 == 1)
            odd.emplace_back(x);
        else
            even.emplace_back(x);
    }

    if (odd.size()) sort(odd.begin(), odd.end(), greater<int>());
    if (even.size()) sort(even.begin(), even.end(), greater<int>());

    i64 ans = -1;
    if (odd.size() >= 2) ans = max(ans, odd[0] + odd[1]);
    if (even.size() >= 2) ans = max(ans, even[0] + even[1]);
    cout << ans << endl;

    return 0;
}