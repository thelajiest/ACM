#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

void solve() {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    reverse(begin(b), end(b));
    map<string, int> mp;
    for (int i = 0; i < n; i++) {
        string now{a[i], b[i]};
        sort(begin(now), end(now));
        mp[now]++;
    }
    int g = 0;
    for (auto [s, cnt] : mp) {
        if ((cnt % 2 == 1) && (s[0] != s[1])) {
            puts("NO");
            return;
        }
        g += cnt % 2;
    }
    if (g > 1)
        puts("NO");
    else
        puts("YES");

    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}