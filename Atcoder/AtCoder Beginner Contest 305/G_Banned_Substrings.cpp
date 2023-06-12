#include <bits/stdc++.h>

using i64 = std::int64_t;

struct TrieNode {
    TrieNode() { id = 0, nxt = std::array<int, 2>(); };
    TrieNode(int _id) : id(_id) {}
    int id;
    std::array<int, 2> nxt = {};
    int &operator[](const int x) { return this->nxt[x]; }
};
template <class Node>
struct trie {
    std::vector<Node> tr;
    trie() { tr.push_back(Node()); };

    int add(const std::string &s) {
        int n = s.size();
        int p = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (!tr[p][c]) {
                tr[p][c] = tr.size();
                tr.emplace_back(tr[p][c]);
            }
            p = tr[p][c];
        }
        return p;
    }

    int size() const { return tr.size(); }
};
template <class Node>
struct ACAutomaton : public trie<Node> {
    std::vector<int> fail;
    ACAutomaton(){};

    void BuildAC() {
        fail.resize(this->tr.size());
        std::queue<int> Q;
        for (int i = 0; i < 2; i++)
            if (this->tr[0][i]) Q.push(this->tr[0][i]);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0; i < 2; i++) {
                if (this->tr[u][i])
                    fail[this->tr[u][i]] = this->tr[fail[u]][i],
                    Q.push(this->tr[u][i]);
                else
                    this->tr[u][i] = this->tr[fail[u]][i];
            }
        }
        return;
    }
};

template <class T>
T power(T a, i64 b) {
    T res = a;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a.size(); j++) res[i][j] = 0;
    for (size_t i = 0; i < a.size(); i++) res[i][i] = 1;
    for (; b; b /= 2, a = a * a) {
        if (b % 2) {
            res = res * a;
        }
    }
    return res;
}

template <int mod>
struct mint {
    int x;
    mint() : x(0) {}
    mint(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    mint &operator+=(const mint &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator-=(const mint &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator*=(const mint &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }
    mint &operator/=(const mint &p) {
        *this *= p.inverse();
        return *this;
    }
    mint operator-() const { return mint(-x); }
    mint operator+(const mint &p) const { return mint(*this) += p; }
    mint operator-(const mint &p) const { return mint(*this) -= p; }
    mint operator*(const mint &p) const { return mint(*this) *= p; }
    mint operator/(const mint &p) const { return mint(*this) /= p; }
    bool operator==(const mint &p) const { return x == p.x; }
    bool operator!=(const mint &p) const { return x != p.x; }
    mint inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return mint(u);
    }
    friend std::ostream &operator<<(std::ostream &os, const mint &p) {
        return os << p.x;
    }
    friend std::istream &operator>>(std::istream &is, mint &a) {
        int64_t t;
        is >> t;
        a = mint<mod>(t);
        return (is);
    }
    int get() const { return x; }
    static constexpr int get_mod() { return mod; }
};
constexpr int P = 998244353;
using Z = mint<P>;

std::vector<std::vector<Z>> operator*(const std::vector<std::vector<Z>> &a,
                                      const std::vector<std::vector<Z>> &b) {
    std::vector<std::vector<Z>> ret(a.size(), std::vector<Z>(a.size(), 0));

    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a.size(); j++)
            for (size_t k = 0; k < a.size(); k++) {
                ret[i][j] += a[i][k] * b[k][j];
            }
    return ret;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 n;
    int m;
    std::cin >> n >> m;

    ACAutomaton<TrieNode> ACAM;
    std::vector<int> endpos;
    for (int i = 0; i < m; i++) {
        std::string s;
        std::cin >> s;
        auto endp = ACAM.add(s);
        endpos.push_back(endp);
    }

    ACAM.BuildAC();

    int sz = ACAM.size();
    std::vector mat(sz, std::vector(sz, Z(0)));

    std::vector<std::vector<int>> adj(sz);
    for (int i = 0; i < sz; i++) {
        if (i != ACAM.fail[i]) adj[ACAM.fail[i]].push_back(i);
    }

    std::vector<int> del(sz);
    for (auto p : endpos) del[p] = 1;
    auto dfs = [&](auto self, int u) -> void {
        for (auto v : adj[u]) {
            del[v] |= del[u];
            self(self, v);
        }
    };
    dfs(dfs, 0);

    for (int i = 0; i < sz; i++) {
        for (auto c : ACAM.tr[i].nxt) {
            mat[i][c] += 1;
        }
    }

    for (int i = 0; i < sz; i++) {
        if (!del[i]) continue;
        for (int j = 0; j < sz; j++) {
            mat[i][j] = 0;
            mat[j][i] = 0;
        }
    }

    auto tmat = power(mat, n);

    Z ans = 0;
    for (int i = 0; i < sz; i++) {
        ans += tmat[0][i];
    }

    std::cout << ans << std::endl;
    return 0;
}