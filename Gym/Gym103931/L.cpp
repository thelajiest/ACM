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
constexpr int N = 3E5;

struct trie {
    vector<array<int, 26>> nxt;
    vector<int> len;
    int cnt = 0;
    void clear() {
        for (int i = 0; i <= cnt; i++) {
            nxt[i].fill(0);
        }
        cnt = 0;
    }
    int add(const string &s) {
        int n = s.size();
        int p = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (!nxt[p][c]) {
                nxt[p][c] = ++cnt;
                len[nxt[p][c]] = len[p] + 1;
            }
            p = nxt[p][c];
        }
        return p;
    }
};
struct ACAutomaton : public trie {
    vector<int> fail;
    ACAutomaton(int _sz) {
        nxt.resize(_sz);
        len.reserve(_sz);
    };

    void BuildAC() {
        fail.resize(cnt + 1);
        queue<int> Q;
        for (int i = 0; i < 26; i++)
            if (nxt[0][i]) Q.push(nxt[0][i]);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0; i < 26; i++) {
                if (nxt[u][i])
                    fail[nxt[u][i]] = nxt[fail[u]][i], Q.push(nxt[u][i]);
                else
                    nxt[u][i] = nxt[fail[u]][i];
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    ACAutomaton ac(N);

    int m;
    cin >> m;
    vector<Z> val(N);
    for (int i = 1; i <= m; i++) {
        string res;
        cin >> res;
        auto p = ac.add(res);
        cin >> val[p];
    }
    ac.BuildAC();
    vector<int> to(ac.cnt + 1);
    vector<vector<int>> adj(ac.cnt + 1);
    for (int i = 0; i <= ac.cnt; i++)
        if (i != ac.fail[i]) adj[ac.fail[i]].push_back(i);

    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (val[u] != 0)
                to[v] = u;
            else
                to[v] = to[u];
            q.push(v);
        }
    }
    vector<Z> dp(n + 1, 0);
    dp[0] = Z(1);
    int p = 0;
    for (int i = 1; i <= n; i++) {
        p = ac.nxt[p][s[i - 1] - 'a'];
        int now = p;
        dp[i] = dp[i - 1];
        while (now != 0) {
            if (i >= ac.len[now]) dp[i] += dp[i - ac.len[now]] * val[now];
            now = to[now];
        }
    }
    for (int i = 1; i <= n; i++) cout << dp[i] << " \n"[i == n];

    return 0;
}