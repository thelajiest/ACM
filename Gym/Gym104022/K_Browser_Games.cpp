#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

struct TrieNode {
    TrieNode() { fa = -1, nxt = map<char, int>(); };
    TrieNode(int _fa) : fa(_fa) {}
    int fa;
    map<char, int> nxt = {};
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
            char c = s[i];
            if (!tr[p][c]) {
                tr[p][c] = tr.size();
                tr.emplace_back(p);
            }
            p = tr[p][c];
        }
        return p;
    }

    int size() const { return tr.size(); }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> s(n);
    for (auto& it : s) cin >> it;
    trie<TrieNode> t;

    vector<int> endpos;
    for (int i = 0; i < n; i++) {
        endpos.push_back(t.add(s[i]));
    }

    vector<int> sum(t.size()), sum2(t.size());
    for (auto ed : endpos) {
        int now = ed;
        while (now != -1) {
            sum[now] += 1;
            now = t.tr[now].fa;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int now = 0;
        now = 0;
        sum[0] -= 1;
        for (auto c : s[i]) {
            now = t.tr[now][c];
            sum[now] -= 1;
        }
        now = 0;
        int highest = 0;
        int res = 0;
        for (auto c : s[i]) {
            now = t.tr[now][c];
            if (sum[now] == 0) {
                ans++;
                ans -= sum2[now];
                res = sum2[now];
                highest = now;
                break;
            }
        }
        now = highest;
        while (now != -1) {
            sum2[now] += 1;
            sum2[now] -= res;
            now = t.tr[now].fa;
        }
        cout << ans << '\n';
    }
    return 0;
}