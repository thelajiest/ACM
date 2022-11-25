#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, N, h, w;

    cin >> H >> W >> N >> h >> w;
    vector<int> mp(N + 1);

    vector<vector<int>> num(H, vector<int>(W));

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) {
            cin >> num[i][j];
            mp[num[i][j]]++;
        }
    vector<vector<int>> ans(H - h + 1, vector<int>(W - w + 1));

    int now = 0;
    for (int i = 0; i + h <= H; i++) {
        vector<int> resmp(N + 1);
        for (int j = 0; j + w <= W; j++) {
            if (i == 0 && j == 0) {
                for (int ii = 0; ii < h; ii++)
                    for (int jj = 0; jj < w; jj++) mp[num[ii][jj]]--;
                int res = 0;
                for (int i = 1; i <= N; i++) {
                    if (mp[i] >= 1) {
                        res++;
                    }
                }
                now = res;
            }
            if (j == 0) resmp = mp;
            ans[i][j] = now;

            for (int ii = i; ii < h + i; ii++) {
                if (mp[num[ii][j]] == 0) now++;
                mp[num[ii][j]]++;
            }
            if (j + w < W) {
                for (int ii = i; ii < h + i; ii++) {
                    mp[num[ii][j + w]]--;
                    if (mp[num[ii][j + w]] == 0) now--;
                }
            }
        }
        now = ans[i][0];
        mp = resmp;
        for (int j = 0; j < w; j++) {
            if (mp[num[i][j]] == 0) now++;
            mp[num[i][j]]++;
        }
        if (i + h < H) {
            for (int j = 0; j < w; j++) {
                mp[num[i + h][j]]--;
                if (mp[num[i + h][j]] == 0) now--;
            }
        }
    }

    for (int i = 0; i <= H - h; i++) {
        for (int j = 0; j <= W - w; j++) cout << ans[i][j] << " ";
        cout << '\n';
    }
    return 0;
}