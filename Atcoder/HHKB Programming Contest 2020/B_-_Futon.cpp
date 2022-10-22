#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> mp(h);
    for (auto& it : mp) cin >> it;
    int ans = 0;
    for (int i = 0; i < h - 1; i++)
        for (int j = 0; j < w; j++)
            if (mp[i][j] == '.' && mp[i + 1][j] == '.') ans++;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w - 1; j++)
            if (mp[i][j] == '.' && mp[i][j + 1] == '.') ans++;

    cout << ans << endl;

    return 0;
}