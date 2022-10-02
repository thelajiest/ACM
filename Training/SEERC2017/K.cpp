#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<int, vector<int>> pos;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pos[x].emplace_back(i);
    }
    vector<int> ans(n + 1);
    int now = n;
    for (auto& [x, lt] : pos) sort(begin(lt), end(lt));
    for (auto [x, lt] : pos) {
        for (auto it : lt) {
            ans[it] = now;
            now--;
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];

    return 0;
}