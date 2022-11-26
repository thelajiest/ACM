#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ans = 0;

    string s;
    cin >> s;

    for (auto c : s) {
        if (c == 'v')
            ans++;
        else
            ans += 2;
    }

    cout << ans;

    return 0;
}