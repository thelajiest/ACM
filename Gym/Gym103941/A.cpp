#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string ans = "1023456789";
    int n;
    cin >> n;

    if (1 <= n && n <= 10) {
        string res;
        res.assign(ans.begin(), ans.begin() + n);
        cout << res;
    } else
        cout << -1;

    return 0;
}