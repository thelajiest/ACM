#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 7;
int dfn[MAX_N], low[MAX_N], scc[MAX_N];
bool in_st[MAX_N];
int order, num;
stack<int> st;
vector<int> e[MAX_N], E[MAX_N];
int siz[MAX_N], dp[MAX_N];
int n, m;

void tarjan(int u) {
    dfn[u] = low[u] = ++order;
    st.push(u);
    in_st[u] = true;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_st[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int tmp;
        num++;
        do {
            tmp = st.top();
            st.pop();
            scc[tmp] = num;
            in_st[tmp] = false;
        } while (tmp != u);
    }
}

void dfs(int u) {
    if (dp[u] != -1) return;
    dp[u] = siz[u] - 1;
    for (auto v : E[u]) {
        dfs(v);
        dp[u] += dp[v] + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int lst = -1;
        for (int j = 0; j < n; ++j) {
            int v;
            cin >> v;
            if (lst != -1) {
                e[lst].emplace_back(v);
            }
            lst = v;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    for (int u = 1; u <= n; ++u) {
        int U = scc[u];
        ++siz[U];
        for (auto v : e[u]) {
            int V = scc[v];
            if (U != V) {
                E[U].emplace_back(V);
            }
        }
    }
    for (int i = 1; i <= num; ++i) {
        sort(E[i].begin(), E[i].end());
        E[i].resize(unique(E[i].begin(), E[i].end()) - E[i].begin());
        dp[i] = -1;
    }
    for (int i = 1; i <= num; ++i) {
        if (dp[i] == -1) {
            dfs(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        int u = scc[i];
        cout << dp[u] << " ";
    }
    cout << "\n";
    return 0;
}