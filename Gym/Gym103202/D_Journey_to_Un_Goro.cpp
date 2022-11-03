#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
vector<vector<char>> ans;
vector<char> res;
i64 n;
i64 mx;
void dfs(int len, int odd, int even, int now) {
    bool ok = true;
    if (len == n) {
        if (abs(odd - even) <= 1) ans.push_back(res);
        return;
    }
    if (ans.size() >= 100) ok = false;
    if (!ok) return;
    for (char it : {'b', 'r'}) {
        res.push_back(it);
        if (it == 'b') {
            if (now == 1) {
                if (odd + 1 <= mx) dfs(len + 1, odd + 1, even, now);
            } else if (even + 1 <= mx)
                dfs(len + 1, odd, even + 1, now);
        } else {
            if (now == 1) {
                if (even + 1 <= mx) dfs(len + 1, odd, even + 1, -now);
            } else if (odd + 1 <= mx)
                dfs(len + 1, odd + 1, even, -now);
        }
        res.pop_back();
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        cout << 'r' << endl;
        return 0;
    }
    mx = max((n + 1) / 2, n + 1 - (n + 1) / 2);
    cout << 1LL * (n + 1) / 2 * (n + 1 - (n + 1) / 2) << '\n';
    dfs(0, 0, 1, -1);
    // cerr << ans.size() << endl;
    for (int i = 0; i < min<int>(ans.size(), 100); i++) {
        for (auto it : ans[i]) cout << it;
        cout << '\n';
    }
    return 0;
}