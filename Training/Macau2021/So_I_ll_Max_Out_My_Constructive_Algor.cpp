#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100;

int T, n;
int G[MAX_N][MAX_N];
vector<int> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> G[i][j];
            }
        }
        ans.clear();
        for (int i = 0; i < n; ++i) {
            if (i & 1) {
                for (int j = 0; j < n; ++j) {
                    ans.push_back(G[i][j]);
                }
            } else {
                for (int j = n - 1; j >= 0; --j) {
                    ans.push_back(G[i][j]);
                }
            }
        }

        int cnt = 0;
        for (int i = 0; i < n * n - 1; ++i) {
            if (ans[i] > ans[i + 1])
                cnt -= 1;
            else
                cnt += 1;
        }

        if (cnt > 0) reverse(ans.begin(), ans.end());
        bool flag = false;
        for (int u : ans) {
            if (flag) cout << ' ';
            cout << u;
            flag = true;
        }
        cout << '\n';
    }

    return 0;
}