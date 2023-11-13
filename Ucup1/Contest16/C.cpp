#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1E6 + 100;

class TrieNode {
   public:
    int cnt, tot;
    TrieNode* next[26];
} a[MAX_N];

int m;
TrieNode rt;

TrieNode* new_node() {
    a[m].cnt = a[m].tot = 0;
    for (int i = 0; i < 26; ++i) a[m].next[i] = nullptr;
    return a + m++;
}

void add(string s) {
    TrieNode* cur = &rt;
    cur->tot += 1;
    for (char c : s) {
        cur = cur->next[c - 'a'] ? cur->next[c - 'a']
                                 : cur->next[c - 'a'] = new_node();
        cur->tot += 1;
    }
    cur->cnt += 1;
}

void clear() {
    rt.cnt = rt.tot = 0;
    for (int i = 0; i < 26; ++i) rt.next[i] = nullptr;
    m = 0;
}

int T;
int n, k;
string ans;

void dfs(TrieNode* cur, int count) {
    count += cur->cnt;  // 当前点全选
    // 每个可能的方向都选一个
    for (int i = 0; i < 26; ++i) {
        if (cur->next[i]) count += 1;
    }
    if (count >= k) return;

    for (int i = 0; i < 26; ++i) {
        if (!cur->next[i]) continue;
        auto v = cur->next[i];

        // 若子方向全选后不够，直接全选（去掉之前的那一个）
        if (count + v->tot - 1 < k) {
            count += v->tot - 1;
            continue;
        }

        // 否则够了，进入（去掉之前的一个）
        ans.push_back(i + 'a');
        dfs(v, count - 1);
        break;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;
    while (T--) {
        cin >> n >> k;
        string s;
        clear();
        while (n--) {
            cin >> s;
            add(s);
        }
        ans.clear();
        dfs(&rt, 0);
        cout << (ans.length() ? ans : "EMPTY") << '\n';
    }

    return 0;
}
/*
2
5 3
gdcpc
gdcpcpcp
suasua
suas
sususua
3 3
a
b
c

*/