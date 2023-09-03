#include <bits/stdc++.h>
#define int long long
#define INF 1e18

using namespace std;

typedef pair<int, int> pii;

const int MAX_N = 2e2 + 7;

vector<pii> dp[MAX_N][MAX_N];
int x[MAX_N], d[MAX_N];

int n;

vector<pii> intersect(vector<pii> &seg, int l, int r) {
    vector<pii> res;
    for (auto p : seg) {
        int _l = max(p.first, l), _r = min(p.second, r);
        if (_l <= _r) {
            res.push_back(make_pair(_l, _r));
        }
    }
    sort(res.begin(), res.end());
    return res;
}

using T = int;
vector<pii> merge(vector<pii> v1, vector<pii> v2) {
    vector<pii> v;
    for (auto p : v1) v.push_back(p);
    for (auto p : v2) v.push_back(p);
    for (auto &[l, r] : v) r++;
    vector<pair<T, T>> buf{v}, res;
    sort(begin(buf), end(buf));
    for (auto &p : buf) {
        res.push_back(p);
        while ((int)res.size() >= 2) {
            int n = res.size();
            if (res[n - 2].second < res[n - 1].first) break;
            pair<T, T> q;
            q.first = res[n - 2].first;
            q.second = max<T>(res[n - 2].second, res[n - 1].second);
            res.pop_back();
            res.pop_back();
            res.push_back(q);
        }
    }
    for (auto &[l, r] : res) r--;
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    for (int i = n; i >= 1; --i) cin >> d[i];
    for (int i = n; i >= 1; --i) {
        dp[i][i].push_back(make_pair(x[i] - d[n], x[i] + d[n]));
        for (int j = i + 1; j <= n; ++j) {
            int k = (i - 1) + (n - j) + 1;
            vector<pii> v1, v2;
            if (i < n) {
                int l = x[i] - d[k], r = x[i] + d[k];
                v1 = intersect(dp[i + 1][j], l, r);
            }
            if (j > 1) {
                int l = x[j] - d[k], r = x[j] + d[k];
                v2 = intersect(dp[i][j - 1], l, r);
            }
            // if (i == 1 && j == 2) {
            //     for (auto p : v1) {
            //         cout << p.first << "#" << p.second << endl;
            //     }
            //     for (auto p : v2) {
            //         cout << p.first << "*" << p.second << endl;
            //     }
            // }
            dp[i][j] = merge(v1, v2);
            // if (i == 1 && j == 2) {
            //     for (auto p : dp[i][j]) {
            //         cout << p.first << "@" << p.second << endl;
            //     }
            // }
        }
    }
    // for (auto p : dp[1][2]) {
    //     cout << p.first << ", " << p.second << endl;
    // }
    int ans = 0;
    for (auto p : dp[1][n]) {
        int l = p.first, r = p.second;
        ans += r - l + 1;
    }
    cout << ans << "\n";
    return 0;
}