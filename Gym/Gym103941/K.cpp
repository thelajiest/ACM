#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <typename G>
struct StronglyConnectedComponents {
   private:
    const G &g;
    vector<vector<int>> rg;
    vector<int> comp, order;
    vector<char> used;
    vector<vector<int>> blng;

   public:
    vector<vector<int>> dag;
    StronglyConnectedComponents(G &_g) : g(_g), used(g.size(), 0) { build(); }

    int operator[](int k) { return comp[k]; }

    vector<int> &belong(int i) { return blng[i]; }

   private:
    void dfs(int idx) {
        if (used[idx]) return;
        used[idx] = true;
        for (auto to : g[idx]) dfs(int(to));
        order.push_back(idx);
    }

    void rdfs(int idx, int cnt) {
        if (comp[idx] != -1) return;
        comp[idx] = cnt;
        for (int to : rg[idx]) rdfs(to, cnt);
    }

    void build() {
        for (int i = 0; i < (int)g.size(); i++) dfs(i);
        reverse(begin(order), end(order));
        used.clear();
        used.shrink_to_fit();

        comp.resize(g.size(), -1);

        rg.resize(g.size());
        for (int i = 0; i < (int)g.size(); i++) {
            for (auto e : g[i]) {
                rg[(int)e].emplace_back(i);
            }
        }
        int ptr = 0;
        for (int i : order)
            if (comp[i] == -1) rdfs(i, ptr), ptr++;
        rg.clear();
        rg.shrink_to_fit();
        order.clear();
        order.shrink_to_fit();

        dag.resize(ptr);
        blng.resize(ptr);
        for (int i = 0; i < (int)g.size(); i++) {
            blng[comp[i]].push_back(i);
            for (auto &to : g[i]) {
                int x = comp[i], y = comp[to];
                if (x == y) continue;
                dag[x].push_back(y);
            }
        }
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    using Graph = vector<vector<int>>;

    Graph g(n);

    vector<pair<int, int>> Edge;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        g[x].push_back(i);
        Edge.emplace_back(x, i);
    }
    StronglyConnectedComponents<Graph> SCC(g);
    vector<int> count(SCC.dag.size());
    vector<int> cir;

    vector<vector<int>> cnt(n + 1);
    for (auto [u, v] : Edge) {
        if (SCC[u] == SCC[v]) count[SCC[u]]++;
    }
    for (int i = 0; i < int(SCC.dag.size()); i++) {
        if (count[i] >= 1) {
            cir.push_back(count[i]);
            if (cnt[count[i]].size() == 0) cnt[count[i]].assign(n + 1, 0);
            cnt[count[i]][0] += count[i];
            function<void(int, int)> dfs = [&](int u, int dep) {
                if (dep != 0) cnt[count[i]][dep]++;
                for (auto v : SCC.dag[u]) {
                    dfs(v, dep + 1);
                }
            };
            dfs(i, 0);
        }
    }

    sort(begin(cir), end(cir));
    cir.resize(unique(begin(cir), end(cir)) - begin(cir));

    for (auto &&it : cnt) {
        if (it.size() == 0) continue;
        for (int j = 1; j < int(it.size()); j++) it[j] += it[j - 1];
    }

    int q;
    cin >> q;

    while (q--) {
        i64 a, b;
        cin >> a >> b;
        if (a == b) {
            cout << n << '\n';
        } else {
            i64 diff = abs(a - b);
            int ans = 0;
            for (auto c : cir) {
                if (diff % c == 0) {
                    ans += cnt[c][min({a, b, i64(n)})];
                }
            }
            cout << ans << '\n';
        }
    }

    return 0;
}