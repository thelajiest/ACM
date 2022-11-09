#include <bits/stdc++.h>
#define int long long
// #define sleepy

using namespace std;

const int MAX_N = 5e6 + 7;
int B, M, N;
int n;

vector<int> pri_fac(int n) {
    vector<int> res;
    int x = n;
    for (int i = 2; i * i <= n; ++i) {
        if (x % i) continue;
        res.emplace_back(i);
        while (x % i == 0) x /= i;
    }
    if (x > 1) res.emplace_back(x);
    return res;
}

vector<int> fac;
vector<int> ans;

void dfs(int idx, int now) {
    if (now > M) return;
    if (idx >= n) {
        ans.emplace_back(now);
        return;
    }
    for (__int128 prod = now; prod <= M;) {
        dfs(idx + 1, prod);
        prod *= fac[idx];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> B >> M >> N;
    fac = pri_fac(B);
    n = fac.size();
    dfs(0, 1);
    sort(ans.begin(), ans.end());

    while (N--) {
        int a;
        cin >> a;
        auto it = lower_bound(ans.begin(), ans.end(), a);
        if (it == ans.end()) {
            cout << "-1\n";
        } else {
            cout << *(it)-a << "\n";
        }
    }
    return 0;
}