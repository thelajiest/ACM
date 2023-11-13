#include <bits/stdc++.h>
using namespace std;

#define int long long
using pii = pair<int, int>;

int T;
pii x[2];
map<vector<int>, int> mp;

vector<int> get_v(int u, int b) {
    vector<int> vec;
    while (u) {
        vec.push_back(u % b);
        u /= b;
    }
    return vec;
}

void solve() {
    cin >> x[0].first >> x[1].first >> x[0].second >> x[1].second;

    mp.clear();
    bool flag = x[0].first < x[1].first;
    if (flag) swap(x[0], x[1]);
    pii ans(-1, -1);
    for (int u = 2; u <= x[0].second; ++u) {
        vector<int> vec = get_v(x[0].first, u);
        if (vec.size() <= 2) break;
        mp[vec] = u;
    }
    for (int u = 2; u <= x[1].second; ++u) {
        vector<int> vec = get_v(x[1].first, u);
        if (vec.size() <= 2) break;
        if (mp.find(vec) != mp.end()) {
            ans = pii(mp[vec], u);
            break;
        }
    }

    if (x[0].first == x[1].first) {
        ans = pii(2, 2);
    }

    for (int u = 1; u <= sqrt(x[1].first + 0.5); ++u) {
        if ((x[0].first - x[1].first) % u) continue;
        int amb = (x[0].first - x[1].first) / u;
        int p = x[1].first / u, q = x[1].first % u;
        int k = (p - q - 1) / (u + 1);
        int b = max(p - k, 2ll);
        int v = x[1].first - u * b;
        if (v < 0 || u >= b) continue;
        int a = b + amb;
        if (a <= x[0].second && b <= x[1].second) {
            ans = pii(a, b);
            break;
        }
    }

    if (-1 == ans.first) {
        cout << "NO" << '\n';
    } else {
        cout << "YES" << '\n';
        if (flag) swap(ans.first, ans.second);
        cout << ans.first << ' ' << ans.second << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}