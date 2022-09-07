#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int _;
    cin >> _;
    while (_--) {
        i64 n;
        cin >> n;
        vector<i64> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        vector<i64> b(n + 1, 0);
        for (int i = 1; i <= n; i++) b[i] = b[i - 1] ^ a[i];

        i64 ans = 0;

        set<int> se;
        se.insert(0);

        for (int i = 1; i <= n; i++) {
            if (se.find(b[i]) != se.end()) {
                se.clear();
                ans++;
            }
            se.insert(b[i]);
        }

        cout << ans << '\n';
    }
    return 0;
}