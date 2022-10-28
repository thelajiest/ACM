#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
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
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return mint(u);
    }
    friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }
    friend istream &operator>>(istream &is, mint &a) {
        int64_t t;
        is >> t;
        a = mint<mod>(t);
        return (is);
    }
    int get() const { return x; }
    static constexpr int get_mod() { return mod; }
};
constexpr int mod = 998244353;
using Z = mint<mod>;
struct TrieNode {
    TrieNode() { id = 0, dep = 0, nxt = array<int, 10>(); };
    TrieNode(int _id, int _dep) : id(_id), dep(_dep) {}
    int id;
    int dep;
    array<int, 10> nxt = {};
    int &operator[](const int x) { return this->nxt[x]; }
};
template <class Node>
struct trie {
    vector<Node> tr;
    trie() { this->tr.push_back(Node()); };

    int add(const string &s) {
        int n = s.size();
        int p = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - '0';
            if (!tr[p][c]) {
                tr[p][c] = tr.size();
                tr.emplace_back(tr[p][c], tr[p].dep + 1);
            }
            p = tr[p][c];
        }
        return p;
    }

    int size() const { return tr.size(); }
};
template <class Node>
struct ACAutomaton : public trie<Node> {
    vector<int> fail;
    ACAutomaton(){};

    void BuildAC() {
        fail.resize(this->tr.size());
        queue<int> Q;
        for (int i = 0; i < 10; i++)
            if (this->tr[0][i]) Q.push(this->tr[0][i]);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0; i < 10; i++) {
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
struct StackNode {
    int c, len, nodep = 0;
    int totlen;
    Z nodeval = 0;
    StackNode(){};
    StackNode(int _c, int _len, int _nodep, int _totlen, Z _nodeval)
        : c(_c), len(_len), nodep(_nodep), totlen(_totlen), nodeval(_nodeval){};
    void output() {
        cerr << "(" << c << "," << len << "," << totlen << "," << nodep << ","
             << nodeval << ")";
    }
};
constexpr int N = 1E6;
array<StackNode, N> s;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Z> val(N);

    int n;
    cin >> n;
    ACAutomaton<TrieNode> ac;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        Z w;
        cin >> w;
        int p = ac.add(s);
        val[p] += w;
    }

    ac.BuildAC();

    vector<vector<int>> adj(ac.size());
    vector<array<array<int, 23>, 10>> to(adj.size());
    vector<array<array<Z, 23>, 10>> w(adj.size());

    for (int i = 0; i < int(ac.size()); i++) {
        if (i != ac.fail[i]) adj[ac.fail[i]].push_back(i);
    }
    auto dfs = [&](auto self, int u, int fa) -> void {
        val[u] += val[fa];
        for (auto v : adj[u]) {
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);
    for (int i = 0; i < ac.size(); i++) {
        for (int c = 0; c < 10; c++) {
            to[i][c][0] = ac.tr[i][c];
            w[i][c][0] = val[ac.tr[i][c]];
        }
    }
    for (int c = 0; c < 10; c++) {
        for (int dep = 1; dep < 23; dep++) {
            for (int i = 0; i < ac.size(); i++) {
                to[i][c][dep] = to[to[i][c][dep - 1]][c][dep - 1];
                w[i][c][dep] =
                    w[i][c][dep - 1] + w[to[i][c][dep - 1]][c][dep - 1];
            }
        }
    }

    auto go = [&](int p, int c, int l) -> int {
        if (l == 0) return p;
        for (int i = 22; i >= 0; i--) {
            if ((l >> i) & 1) p = to[p][c][i];
        }
        assert(p < ac.size());
        return p;
    };
    auto goval = [&](int p, int c, int l) {
        if (l == 0) return Z(0);
        Z res = 0;
        for (int i = 22; i >= 0; i--) {
            if ((l >> i) & 1) {
                res += w[p][c][i];
                p = to[p][c][i];
            }
        }
        assert(p < ac.size());

        return res;
    };
    string qry;
    cin >> qry;
    int m = qry.size();

    int p = 1, nodep = 0;
    Z sum = 0;
    for (int i = 0, j; i < m; i = j) {
        int c = qry[i] - '0';
        j = i;
        while (j < m && qry[i] == qry[j]) {
            nodep = ac.tr[nodep][c];
            sum += val[nodep];
            j++;
        }
        s[p++] = StackNode(c, j - i, nodep, i, sum);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, C;
            cin >> l >> C;

            int L = 1, R = p - 1;
            while (L < R) {
                int mid = (L + R + 1) / 2;
                if (m - l >= s[mid].totlen)
                    L = mid;
                else
                    R = mid - 1;
            }
            if (m - l - s[L].totlen == 0) {
                s[L] =
                    StackNode(C, l, go(s[L - 1].nodep, C, l), m - l,
                              s[L - 1].nodeval + goval(s[L - 1].nodep, C, l));
                p = L + 1;

            } else {
                s[L] =
                    StackNode(s[L].c, m - l - s[L].totlen,
                              go(s[L - 1].nodep, s[L].c, m - l - s[L].totlen),
                              s[L].totlen,
                              s[L - 1].nodeval + goval(s[L - 1].nodep, s[L].c,
                                                       m - l - s[L].totlen)),
                s[L + 1] = StackNode(C, l, go(s[L].nodep, C, l), m - l,
                                     s[L].nodeval + goval(s[L].nodep, C, l));
                p = L + 2;
            }
        } else {
            int l;
            cin >> l;
            int L = 1, R = p - 1;
            while (L < R) {
                int mid = (L + R + 1) / 2;
                if (l >= s[mid].totlen)
                    L = mid;
                else
                    R = mid - 1;
            }
            if (l == s[L].totlen) {
                cout << s[L - 1].nodeval << '\n';
            } else
                cout << s[L - 1].nodeval +
                            goval(s[L - 1].nodep, s[L].c, l - s[L].totlen)
                     << '\n';
        }
    }
    return 0;
}