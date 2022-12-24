#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    cin >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> col(n, 0);
    vector<int> st;
    auto dfs = [&](auto self, int u, int p) -> bool {
        st.push_back(u);
        col[u] = p;
        bool flag = true;
        for (auto v : adj[u]) {
            if (col[v] == 0)
                flag &= self(self, v, -p);
            else
                flag &= (col[v] != col[u]);
        }
        return flag;
    };
    bool flag = true;
    i64 ans = 0;
    i64 cnt = 0;
    for (int i = 0; i < n; i++) {
        if (col[i] == 0) {
            st.clear();
            flag &= dfs(dfs, i, 1);
            ans += 1LL * (st.size()) * cnt;
            cnt += st.size();
            i64 sum = 0;
            for (auto p : st) {
                if (col[p] == 1) sum++;
            }
            ans += sum * (1LL * (st.size() - sum));
        }
    }
    if (!flag) {
        cout << 0 << endl;
    } else {
        cout << ans - m << endl;
    }
    return 0;
}