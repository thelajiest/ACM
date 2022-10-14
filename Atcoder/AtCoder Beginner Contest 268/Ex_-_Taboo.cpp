#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

struct TrieNode {
    TrieNode() { id = 0, dep = 0, nxt = array<int, 26>(); };
    TrieNode(int _id, int _dep) : id(_id), dep(_dep) {}
    int id;
    int dep;
    array<int, 26> nxt = {};
    int& operator[](const int x) { return this->nxt[x]; }
};
template <class Node>
struct trie {
    vector<Node> tr;
    trie() { tr.push_back(Node()); };

    int add(const string& s) {
        int n = s.size();
        int p = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
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

    string s;
    cin >> s;

    int m;
    cin >> m;
    ACAutomaton<TrieNode> ac;
    vector<int> pos(m + 1);
    for (int i = 1; i <= m; i++) {
        string res;
        cin >> res;
        pos[i] = ac.add(res);
    }
    ac.BuildAC();
    vector<int> vis(ac.size());
    for (int i = 1; i <= m; i++) vis[pos[i]] = 1;
    vector<vector<int>> adj(ac.size());
    for (int i = 0; i < ac.size(); i++) {
        if (ac.fail[i] != i) adj[ac.fail[i]].push_back(i);
    }
    vector<int> to(ac.size(), -1);
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if ((to[u] == -1) && vis[u]) {
            to[u] = u;
        }
        for (auto v : adj[u]) {
            to[v] = to[u];
            q.push(v);
        }
    }

    int p = 0;
    vector<pair<int, int>> seg;

    for (int i = 0; i < s.size(); i++) {
        p = ac.tr[p][s[i] - 'a'];
        if (to[p] == -1) continue;
        seg.emplace_back(i - ac.tr[to[p]].dep + 1, i);
    }

    sort(seg.begin(), seg.end(),
         [&](const pair<int, int>& a, const pair<int, int>& b) {
             return a.second < b.second;
         });

    int ans = 0;

    int nowr = -1;
    for (auto [l, r] : seg) {
        if (l > nowr) {
            nowr = max(nowr, r);
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}