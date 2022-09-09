#include <bits/stdc++.h>
using namespace std;
#define int long long

typedef pair<int, int> pii;
const int MAX_N = 100 + 7;
int n, m;
int a[MAX_N][MAX_N];
int x, y, z;
const int fi[4] = {0, 1, 0, -1};
const int fj[4] = {1, 0, -1, 0};

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }
    cin >> x >> y >> z;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            bool flag = false;
            if (x != a[i][j]) continue;
            for (int k = 0; !flag && k < 4; ++k) {
                if (y == a[i + fi[k]][j + fj[k]] &&
                    z == a[i + fi[(k + 1) % 4]][j + fj[(k + 1) % 4]]) {
                    flag = true;
                }
            }
            if (flag) {
                cout << i - 1 << ' ' << j - 1 << '\n';
            }
        }
    }

    return 0;
}