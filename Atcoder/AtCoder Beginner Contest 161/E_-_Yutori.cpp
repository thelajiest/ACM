#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, c;
    cin >> n >> k >> c;
    string s;
    cin >> s;
    vector<int> x, y;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'o') x.push_back(i), i += c;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'o') y.push_back(i), i -= c;
    }
    y.resize(k);
    reverse(begin(y), end(y));

    for (int i = 0; i < k; i++)
        if (x[i] == y[i]) cout << x[i] + 1 << '\n';

    return 0;
}