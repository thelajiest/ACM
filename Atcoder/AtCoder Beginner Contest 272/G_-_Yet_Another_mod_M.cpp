#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937 mt(time(0));
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto&& it : a) cin >> it;

    int Rnums = 100;
    while (Rnums--) {
        std::uniform_int_distribution<int> rd(0, n - 1);
        int x = rd(mt);
        int y = rd(mt);
        while (x == y) y = rd(mt);

        assert(0 <= x && x < n);
        assert(0 <= y && y < n);

        int diff = abs(a[x] - a[y]);

        vector<int> div;
        for (int i = 1; i * i <= diff; i++) {
            if (diff % i == 0) {
                div.push_back(i);
                if (i != diff / i) div.push_back(diff / i);
            }
        }

        for (auto M : div) {
            if (M < 3 || M > 1E9) continue;
            unordered_map<int, int> mp;
            for (auto it : a) mp[it % M]++;
            for (auto [x, cnt] : mp)
                if (cnt > n - cnt) {
                    cout << M << endl;
                    return 0;
                }
        }
    }

    cout << -1 << endl;

    return 0;
}