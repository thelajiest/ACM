#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

void solve() {
    string s;
    cin >> s;

    array<int, 10> cnt;
    cnt.fill(0);
    char now = '9';
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (now >= s[i]) {
            now = s[i];
            cnt[s[i] - '0']++;
        } else {
            cnt[min(9, s[i] - '0' + 1)]++;
        }
    }
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j < cnt[i]; j++) cout << i;
    }
    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}