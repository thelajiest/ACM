#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> t(n + 1);
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        t[i].push_back(x);
        t[x].push_back(i);
    }
    return 0;
}