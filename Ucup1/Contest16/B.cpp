#include <bits/stdc++.h>
using namespace std;

#define int long long
using pii = pair<int, int>;
const int MAX_N = 1E6 + 100;

int T;
int n, m;
set<pii> st;
pii x[MAX_N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int a;
                cin >> a;
                x[a] = pii(i, j);
            }
        }
        st.clear();

        int ans = 0;
        st.insert(pii(1, 1)), st.insert(pii(n, m));
        for (ans = 0; ans < n * m; ++ans) {
            int u = x[ans].first, v = x[ans].second;
            if (1 == u && 1 == v) continue;
            if (n == u && m == v) continue;
            auto it = st.lower_bound(pii(u, v));
            it--;
            int lx = it->first, ly = it->second;
            it++;
            int rx = it->first, ry = it->second;
            // cerr << "err " << lx << ' ' << ly << ' ' << rx << ' ' << ry <<
            // endl;
            if (lx <= u && u <= rx && ly <= v && v <= ry) {
                st.insert(pii(u, v));
            } else {
                break;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}