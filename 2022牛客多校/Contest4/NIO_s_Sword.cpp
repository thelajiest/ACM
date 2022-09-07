#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = i % n;
    int aa = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        while ((((a[i] - aa) % n + n) % n) > 9) {
            a[i] = a[i] * 10 % n;
            ans++;
        }
        ans++;
        aa = a[i];
    }
    cout << ans;
}