#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    // std::ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;

    cin >> n;

    vector<vector<pair<int, int>>> go(n + 1);
    vector<vector<pair<int, int>>> bk(n + 1);
    vector<pair<int, int>> gg;
    int id = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 11; j++) {
            if (i + (1 << j) > n) break;
            go[i].push_back({i + (1 << j), ++id});
            bk[i + (1 << j)].push_back({i, id});
            gg.push_back({i, i + (1 << j)});
        }
    }
    int full = gg.size();
    for (int i = 1; i <= n; i++) {
        gg.push_back({i, i});
    }
    cout << gg.size() << endl;
    cout.flush();

    for (auto [x, y] : gg) {
        cout << x << " " << y << endl;
        cout.flush();
    }
    int q;
    cin >> q;

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << full + l << " " << full + l << endl;
            cout.flush();
            continue;
        }
        int mxL = l, id1;
        for (auto [g, id] : go[l]) {
            if (g > r) break;
            if (g > mxL) {
                mxL = g;
                id1 = id;
            }
        }
        int mnR = r, id2;
        for (auto [g, id] : bk[r]) {
            if (g >= l) {
                mnR = g;
                id2 = id;
                break;
            }
        }

        cout << id1 << " " << id2 << endl;
        cout.flush();
    }
    return 0;
}