#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'o') a[i] |= (1 << j);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if ((a[i] | a[j]) == ((1 << (m)) - 1)) ans++;
        }
    }

    cout << ans;

    return 0;
}