#include <bits/stdc++.h>
#define int long long

using namespace std;

int n;

int get(int s) {
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int now = 0;
        for (int j = i; j < n; ++j) {
            now += ((s >> j) & 1);
            if (now & 1) {
                ++res;
            }
        }
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n;
    int ans = 0;
    for (int i = 0; i < (1 << n); ++i) {
        ans = max(ans, get(i));
    }
    vector<string> hhh;
    for (int s = 0; s < (1 << n); ++s) {
        if (get(s) == ans) {
            string now = "";
            for (int i = 0; i < n; ++i) {
                if ((s >> i) & 1) {
                    now = now + "r";
                } else {
                    now = now + "b";
                }
            }
            hhh.emplace_back(now);
        }
    }
    cout << ans << "\n";
    sort(hhh.begin(), hhh.end());
    for (auto s : hhh) {
        cout << s << "\n";
    }
    return 0;
}