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
        int n;
        cin >> n;
        i64 res = 0;
        for (int i = 1; i <= n; i++) res += i * (n - i + 1);
        int now = 1;
        for (int i = 2; i * i <= res; i++) {
            if (res % i == 0) now = max(i, now);
        }
        i64 width = res / now;
        vector<VI> ans(now + 1);
        vector<int> mp(n + 1);
        for (int i = 1; i <= n; i++) mp[i] = n - i + 1;
        for (int i = 1; i <= now; i++) {
            int sum = width;
            while (sum != 0) {
                int fst;
                for (int j = min(sum, n); j >= 1; j--) {
                    if (mp[j] >= 1) {
                        fst = j;
                        break;
                    }
                }
                sum -= fst;
                mp[fst]--;
                ans[i].push_back(fst);
            }
        }
        // for (int i = 1; i <= n; i++) assert(mp[i] == 0);
        // cerr << endl;
        cout << (now + width) * 2 << endl;
        for (int i = 1; i <= now; i++) {
            int noww = 0;
            for (auto p : ans[i]) {
                auto solve = [&](int c, int noww, int x) {
                    cout << noww << " " << c - 1 << " " << noww + x << " " << c
                         << endl;
                };
                solve(i, noww, p);
                noww += p;
            }
        }
    }
}