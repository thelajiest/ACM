#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n;
    cin >> n;

    vector<i64> ans;

    function<void(i64, int)> dfs = [&](i64 x, int pos) {
        ans.push_back(x);
        for (i64 i = pos + 1; i <= 60; i++) {
            if ((x >> i) & 1) dfs(x ^ (1ll << i), i);
        }
    };
    dfs(n, -1);
    sort(ans.begin(), ans.end());
    for (auto it : ans) cout << it << '\n';

    return 0;
}