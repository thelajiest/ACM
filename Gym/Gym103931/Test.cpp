#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

struct TrieNode {
    TrieNode() { id = 0, nxt = array<int, 26>(); };
    TrieNode(int _id) : id(_id) {}
    int id;
    array<int, 26> nxt = {};
    int &operator[](const int x) { return this->nxt[x]; }
};
template <class Node>
struct trie {
    vector<Node> tr;
    trie() { tr.push_back(Node()); };

    int add(const string &s) {
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
    vector<int> fail;
    ACAutomaton() { this->tr.push_back(Node()); };

    void BuildAC() {
        fail.resize(this->tr.size());
        queue<int> Q;
        for (int i = 0; i < 26; i++)
            if (this->tr[0][i]) Q.push(this->tr[0][i]);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0; i < 26; i++) {
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

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    ACAutomaton<TrieNode> ac;
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        string res;
        cin >> res;
        pos[i] = ac.add(res);
    }

    ac.BuildAC();

    vector<int> val(ac.size());
    vector<vector<int>> adj(ac.size());
    for (int i = 0; i < ac.size(); i++) {
        if (i != ac.fail[i]) adj[ac.fail[i]].push_back(i);
    }

    string s;
    cin >> s;
    int p = 0;
    for (auto it : s) {
        p = ac.tr[p][it - 'a'];
        val[p]++;
    }

    function<void(int)> dfs = [&](int u) {
        for (auto v : adj[u]) {
            dfs(v);
            val[u] += val[v];
        }
    };
    dfs(0);

    for (int i = 1; i <= n; i++) cout << val[pos[i]] << '\n';

    return 0;
}