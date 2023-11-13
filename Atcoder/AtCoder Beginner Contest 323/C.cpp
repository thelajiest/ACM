#include <bits/stdc++.h>
using i64 = std::int64_t;
using u64 = std::uint64_t;

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

constexpr u64 C = 1E11 + 3;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string s;
    std::cin >> n >> s;

    std::string rs;
    for (int i = n - 1; i >= 0; i--) {
        rs.push_back(s[i]);
    }

    PAM pam, rpam;
    std::vector<int> p(n), rp(n);
    for (int i = 0; i < n; i++) {
        p[i] = pam.insert(s[i]);
    }

    for (int i = 0; i < n; i++) {
        rp[i] = rpam.insert(rs[i]);
    }

    auto fail = pam.getFailTree();
    auto rfail = rpam.getFailTree();

    auto get1 = [&](int l, int r) {
        int pos = p[l];
        for (int i = 20; i >= 0; i--) {
            if (pam.pam[fa[pos][i]].len <= r - l + 1) pos = fa[pos][i];
        }
    };
    std::vector<u64> power(n + 1), hash(n + 1), rhash(n + 1);
    power[0] = 1;

    for (int i = 0; i < n; i++) {
        power[i + 1] = power[i] * C;
        hash[i + 1] = hash[i] * C + s[i];
        rhash[i + 1] = rhash[i] * C + rs[i];
    }

    auto getHash = [&](int a, int b) -> u64 {
        // [a, b)
        return hash[b] - hash[a] * power[b - a];
    };
    auto getrHash = [&](int a, int b) -> u64 {
        // [a, b)
        return rhash[b] - rhash[a] * power[b - a];
    };

    int q;
    std::cin >> q;

    while (q--) {
        int l, r;
        std::cin >> l >> r;

        l--, r--;
        int rl = n - r - 1;
        int rr = n - l - 1;
        std::cerr << rl << " " << rr << std::endl;
        if (getHash(l, r + 1) == getrHash(rl, rr + 1)) {
            std::cout << "0 0\n";
            continue;
        }

        if (s[l] != s[r]) {
            int prefix =
        }
        int lo = 1, hi = (r - l + 1) / 2;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (getHash(l, l + mid + 1) == getrHash(rl, rl + mid + 1))
                lo = mid;
            else
                hi = mid - 1;
        }
    }
    return 0;
}