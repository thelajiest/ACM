#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <int ALPHA_SIZE>
struct trie {
    vector<array<int, ALPHA_SIZE>> nxt;
    int cnt = 0;
    trie(int _sz) : nxt(_sz){};
    void clear() {
        for (int i = 0; i <= cnt; i++) {
            nxt[i].fill(0);
        }
        cnt = 0;
    }
    int add(const string& s) {
        int n = s.size();
        int p = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (!nxt[p][c]) nxt[p][c] = ++cnt;
            p = nxt[p][c];
        }
        return p;
    }
};

template <int ALPHA_SIZE>
vector<int> BuildAC(trie<ALPHA_SIZE>& tr) {
    queue<int> Q;
    vector<int> fail(tr.cnt + 1);
    for (int i = 0; i < ALPHA_SIZE; i++)
        if (tr.nxt[0][i]) Q.push(tr.nxt[0][i]);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < ALPHA_SIZE; i++) {
            if (tr.nxt[u][i])
                fail[tr.nxt[u][i]] = tr.nxt[fail[u]][i], Q.push(tr.nxt[u][i]);
            else
                tr.nxt[u][i] = tr.nxt[fail[u]][i];
        }
    }
    return fail;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    constexpr int ALPHA_SIZE = 12;
    constexpr int N = 4E6 + 1;
    trie<ALPHA_SIZE> tr(N);

    vector<int> val(N);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        string s;
        cin >> s;
        int now = tr.add(s);
        val[now] += c;
    }

    vector<int> fail;
    fail = BuildAC<ALPHA_SIZE>(tr);
    vector<array<int, ALPHA_SIZE>> dp(n);

    for (int i = 0; i < ALPHA_SIZE; i++) {
    }
    return 0;
}