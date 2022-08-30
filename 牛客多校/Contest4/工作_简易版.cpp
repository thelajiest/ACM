#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<vector<vector<int>>> mp(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        mp[i].assign(401, vector<int>(401, 401));
        for (int j = 1; j <= m; j++) {
            int a, b, c;
            a--, b--, c--;
            cin >> a >> b >> c;
            mp[i][a][b] = min(mp[i][a][b], c);
        }
        for (int j = 0; j <= 400; j++)
            for (int k = 0; k <= 400; k++)
                mp[i][j][k] =
                    min({mp[i][j][k], (j >= 1) ? mp[i][j - 1][k] : 400,
                         (k >= 1) ? mp[i][j][k - 1] : 400});
    }
    int seed;
    cin >> seed;
    mt19937 rng(seed);
    uniform_int_distribution<> u(1, 400);

    auto solve = [&](int a, int b, int c) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (c >= mp[i][a][b]) {
                ans++;
            }
        }
        // cerr << ans << endl;
        return ans;
    };

    int lastans = 0;
    int ans = 0;
    for (int i = 1; i <= q; i++) {
        int IQ = (u(rng) ^ lastans) % 400;
        int EQ = (u(rng) ^ lastans) % 400;
        int AQ = (u(rng) ^ lastans) % 400;
        lastans = solve(IQ, EQ, AQ);
        ans = (1LL * ans * seed + lastans) % 998244353;
    }
    cout << ans << "\n";
}