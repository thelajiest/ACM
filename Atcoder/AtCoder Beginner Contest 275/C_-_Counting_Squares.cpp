#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<char>> s(9);
    for (auto& it : s) {
        string res;
        cin >> res;
        it = {res.begin(), res.end()};
    }
    int ans = 0;

    vector<pair<int, int>> mp;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (s[i][j] == '#') mp.push_back({i, j});
        }
    }

    for (int i = 0; i < mp.size(); i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < j; k++) {
                for (int t = 0; t < k; t++) {
                    map<int, int> mpp;
                    auto dis = [&](pair<int, int> a, pair<int, int> b) {
                        auto [x, y] = a;
                        auto [xx, yy] = b;
                        return (x - xx) * (x - xx) + (y - yy) * (y - yy);
                    };
                    vector<pair<int, int>> tt;
                    tt.push_back(mp[i]);
                    tt.push_back(mp[j]);
                    tt.push_back(mp[k]);
                    tt.push_back(mp[t]);
                    for (int gg = 0; gg < 4; gg++)
                        for (int ggg = 0; ggg < gg; ggg++)
                            mpp[dis(tt[gg], tt[ggg])]++;
                    vector<int> tttttt;
                    for (auto [l, r] : mpp) tttttt.push_back(r);
                    sort(tttttt.begin(), tttttt.end());
                    if (tttttt[0] == 2 && tttttt[1] == 4) ans++;
                }
            }
        }
    }
    cout << ans;
    return 0;
}