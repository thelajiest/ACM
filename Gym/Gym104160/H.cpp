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
        pam.reserve(4E6);
        pam.emplace_back(0);
        pam.emplace_back(-1);
        pam[0].fail = 1;
    };

    void exPAM() {
        s = "$";
        last = 0;
    }
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
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> s(n);
    std::vector<int> pos;
    PAM pam;
    int m = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        m += s[i].size();
        for (auto c : s[i]) {
            pos.push_back(pam.insert(c));
        }
        pam.exPAM();
    }

    std::vector<i64> cnt(pam.size());
    for (int i = 0; i < m; i++) {
        cnt[pos[i]] = 1;
    }

    std::vector<std::vector<int>> div(m + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j += i) div[j].push_back(i);
    }
    auto adj = pam.getFailTree();

    i64 ans = 0;
    std::vector<i64> sum(m + 1);
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        if (pam[u].len >= 1) {
            for (const auto& d : div[pam[u].len]) {
                sum[d] += cnt[u];
            }
        }
        if (fa != -1 && pam[fa].len >= 1) {
            int len = pam[u].len - pam[fa].len;
            if ((pam[u].len % len) == 0) {
                i64 prefix = sum[len] - cnt[u];
                ans += prefix * cnt[u];
            }
        }
        for (const auto& v : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }
        if (pam[u].len >= 1) {
            for (const auto& d : div[pam[u].len]) {
                sum[d] -= cnt[u];
            }
        }
    };

    dfs(dfs, 1, -1);
    ans *= 2;
    for (int i = 0; i < pam.size(); i++) {
        ans += cnt[i];
    }
    std::cout << ans << std::endl;

    return 0;
}