#include <bits/stdc++.h>

using i64 = std::int64_t;

struct PAM {
    struct node {
        std::array<int, 26> next;
        int len, fail;
        node(int L) {
            next.fill(0);
            len = L;
            fail = 0;
        }
    };

    int last;
    std::string s;
    std::vector<node> pam;
    PAM() {
        last = 0;
        s = "$";
        pam.emplace_back(0);
        pam.emplace_back(-1);
        pam[0].fail = 1;
    };

    int getFail(int x) {
        int tot = s.size() - 1;
        while (s[tot - pam[x].len - 1] != s[tot]) {
            x = pam[x].fail;
        }
        return x;
    }

    int insert(char c) {
        s.push_back(c);
        int now = getFail(last);
        if (pam[now].next[c - 'a'] == 0) {
            pam.emplace_back(pam[now].len + 2);
            pam.back().fail = pam[getFail(pam[now].fail)].next[c - 'a'];
            pam[now].next[c - 'a'] = pam.size() - 1;
        }
        last = pam[now].next[c - 'a'];

        return last;
    }

    std::vector<std::vector<int>> getFailTree() {
        // root at 1 !!!
        std::vector<std::vector<int>> adj(pam.size());
        for (int i = 1; i < pam.size(); i++) {
            if (pam[i].fail != -1) {
                adj[i].push_back(pam[i].fail), adj[pam[i].fail].push_back(i);
            }
        }
        return adj;
    }

    node& operator[](const int x) { return this->pam[x]; }
    int size() const { return pam.size(); }
};
void solve() {
    std::string s;
    std::cin >> s;

    PAM maton;

    std::vector<int> pos;
    for (auto c : s) {
        auto p = maton.insert(c);
        pos.emplace_back(p);
    }

    auto adj = maton.getFailTree();

    constexpr int LOG = 30;
    std::vector<std::array<int, LOG>> par(maton.size());
    for (int i = 0; i < maton.size(); i++) par[i].fill(-1);

    auto build = [&](auto&& self, int u, int fa) -> void {
        par[u][0] = fa;
        for (int i = 1; i < LOG; i++) {
            if (par[u][i - 1] != -1) par[u][i] = par[par[u][i - 1]][i - 1];
        }
        for (auto v : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }
    };
    build(build, 1, -1);

    std::vector<int> cnt(maton.size());
    std::vector<i64> sum(maton.size());

    for (int i = 1; i < maton.size(); i++) {
        if (maton[i].len % 2 == 1) continue;
        int p = i;
        for (int j = LOG - 1; j >= 0; j--) {
            if (par[p][j] != -1 && maton[par[p][j]].len >= maton[i].len / 2) {
                p = par[p][j];
            }
            if (p == -1) break;
        }
        if (p == -1) continue;
        if (maton[p].len == maton[i].len / 2) cnt[i]++;
    }

    auto dfs = [&](auto&& self, int u, int fa) -> void {
        sum[u] = cnt[u];
        if (fa != -1) sum[u] += sum[fa];
        for (const auto& v : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }
    };

    dfs(dfs, 1, -1);

    i64 ans = 0;
    for (auto p : pos) {
        ans += sum[p];
    }

    std::cout << ans << '\n';

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}