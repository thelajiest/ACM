#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<pair<int, int>> seg, ans;
    for (int i = 1, j; i <= n; i = j) {
        j = i;
        if (a[j] == 0) {
            j++;
            continue;
        }
        while (a[j] != 0 && j <= n) j++;
        seg.push_back({i, j - 1});
    }
    // for (auto [l, r] : seg) cerr << l << " " << r << endl;
    // cerr << "adasd" << endl;
    int nd = 0;
    int lst;
    for (int i = 0; i < seg.size(); i++) {
        auto [l, r] = seg[i];
        if ((r - l + 1 + nd) % 2 == 0) {
            if (nd == 0) {
                for (int j = l; j <= r;) {
                    if (a[j] == a[j + 1]) {
                        ans.emplace_back(j, j + 1);
                        j += 2;
                    } else {
                        ans.emplace_back(j, j);
                        j++;
                    }
                }
            } else {
                if (a[l] != a[lst]) {
                    ans.emplace_back(lst, l);
                } else {
                    ans.emplace_back(lst, lst);
                    if (lst + 1 <= l - 2) ans.emplace_back(lst + 1, l - 2);
                    ans.emplace_back(l - 1, l);
                }
                nd = 0;
                for (int j = l + 1; j <= r;) {
                    if (a[j] == a[j + 1]) {
                        ans.emplace_back(j, j + 1);
                        j += 2;
                    } else {
                        ans.emplace_back(j, j);
                        j++;
                    }
                }
            }
        } else {
            for (int j = l; j <= r - 1;) {
                if (a[j] == a[j + 1]) {
                    ans.emplace_back(j, j + 1);
                    j += 2;
                } else {
                    ans.emplace_back(j, j);
                    j++;
                }
            }
            nd = 1;
            lst = r;
        }
    }
    if (nd) {
        cout << "-1" << '\n';
        return;
    }
    if (ans.size() == 0) {
        cout << 1 << '\n';
        cout << 1 << " " << n << '\n';
        return;
    }
    sort(ans.begin(), ans.end());
    vector<pair<int, int>> zz;
    for (int i = 0; i < ans.size() - 1; i++) {
        if (ans[i].second + 1 <= ans[i + 1].first - 1)
            zz.emplace_back(ans[i].second + 1, ans[i + 1].first - 1);
    }

    if (ans.back().second != n) zz.emplace_back(ans.back().second + 1, n);
    for (auto p : zz) ans.push_back(p);
    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (auto [l, r] : ans) cout << l << ' ' << r << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
};