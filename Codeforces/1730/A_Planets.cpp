#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

void solve() {
    int n, c;
    cin >> n >> c;
    constexpr int N = 101;
    array<int, N> cnt;
    cnt.fill(0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (cnt[i] >= c)
            ans += c;
        else {
            ans += cnt[i];
        }
    }
    cout << ans << '\n';
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