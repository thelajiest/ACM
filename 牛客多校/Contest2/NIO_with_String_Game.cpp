#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using pii = pair<int, int>;
using VI = vector<int>;

struct trie {
    vector<array<int, 26>> nxt;
    vector<int> isp;
    int cnt;
    trie() {}
    trie(int sz) {
        nxt.resize(sz);
        isp.resize(sz);

        cnt = 0;
    }
    int insert(const string& s) {
        int p = 0;
        int l = s.length();
        for (int i = 0; i < l; i++) {
            int c = s[i] - 'a';
            if (!nxt[p][c]) nxt[p][c] = ++cnt;
            p = nxt[p][c];
        }
        isp[p] = 1;
        return p;
    }
};
template <class T>
struct segment_tree {
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mid ((l + r) >> 1)
    vector<T> data;
    segment_tree(){};
    segment_tree(int sz) { data.resize(sz << 2 | 1); }
    void build(const vector<T>& a, int l, int r, int p) {
        if (l == r) {
            data[p] = a[l];
            return;
        }
        build(a, l, mid, ls(p));
        build(a, mid + 1, r, rs(p));
        data[p] = data[ls(p)] + data[rs(p)];
    }
    void add(int pos, T val, int l, int r, int p) {
        if (l == r) {
            data[p] += val;
            return;
        }
        if (pos <= mid)
            add(pos, val, l, mid, ls(p));
        else
            add(pos, val, mid + 1, r, rs(p));
        data[p] = data[ls(p)] + data[rs(p)];
    }
    T query(int nodel, int noder, int l, int r, int p) {
        if (nodel <= l && r <= noder) {
            return data[p];
        }
        T sum = 0;
        if (nodel <= mid) sum += query(nodel, noder, l, mid, ls(p));
        if (mid < noder) sum += query(nodel, noder, mid + 1, r, rs(p));
        return sum;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    string s;
    vector<string> s2(n);

    cin >> s;
    int sum_len_s2(0);
    for (auto&& it : s2) {
        cin >> it;
        sum_len_s2 += it.size();
    }

    trie T(sum_len_s2 + 1);

    using Q = tuple<int, int, char>;

    vector<Q> qry(q);
    for (auto&& [op, k, c] : qry) {
        cin >> op;
        if (op == 1 || op == 3) cin >> k >> c;
        if (op == 2) cin >> k;
        if (op == 1) {
            s2[k - 1] += c;
        }
    }
    vector<int> where(n);
    for (int i = 0; i < n; i++) where[i] = T.insert(s2[i]);

    vector<int> dfn(T.cnt + 1);

    vector<array<int, 22>> fa(T.cnt + 1);
    vector<array<int, 26>> go(T.cnt + 1);
    vector<int> dep(T.cnt + 1);
    vector<int> siz(T.cnt + 1);
    int ord = 0;
    function<void(int, int)> dfs = [&](int x, int f) {
        dfn[x] = ++ord;
        siz[x] = 1;
        fa[x][0] = f;
        dep[x] = dep[f] + 1;
        for (int i = 1; i < fa[x].size(); i++) {
            fa[x][i] = fa[fa[x][i - 1]][i - 1];
        }
        for (int i = 0; i < 25; i++) {
            if (T.nxt[x][i]) {
                go[x][i] = go[T.nxt[x][i]][i];
                dfs(T.nxt[x][i], x);
                go[x][i] = go[T.nxt[x][i]][i];
                siz[x] += siz[T.nxt[x][i]];
            }
        }
        return;
    };
    dfs(0, 0);
    auto uptrie = [&](pair<int, int> pos, int k) -> pair<int, int> {
        if (pos.second >= k)
            return {pos.first, pos.second - k};
        else
            k -= pos.second;
        int p = pos.first;

        for (int i = fa[p].size(); i >= 0; i--) {
            if ((k >> i) & 1) {
                p = fa[p][i];
            }
        }
        return {p, 0};
    };

    auto downtrie = [&](pair<int, int> pos, int k, int c) -> pair<int, int> {
        if (pos.second >= 0) return {pos.first, pos.second + k};
        int now = dep[go[pos.first][c]] - dep[pos.first] - k;
        if (now < 0)
            return {pos.first, -now};
        else {
            pos.first = go[pos.first][c];
            return uptrie({pos.first, 0}, k);
        }
    };
    vector<int> val(ord + 1, 0);
    for (int i = 0; i <= T.cnt; i++) {
        val[dfn[i]] += T.isp[i];
    }
    for (int i = 1; i <= ord; i++) cerr << val[i] << " ";
    cout << endl;
    segment_tree<int> segT(ord);

    segT.build(val, 1, ord, 1);

    vector<pair<int, int>> pos_s;
    auto gao = [&](const string& s) -> pair<int, int> {
        int l = s.length();
        int p = 0;
        for (int i = 0; i < l; i++) {
            int c = s[i] - 'a';
            if (!T.nxt[p][c]) return {p, l - i};
            p = T.nxt[p][c];
        }
        return {p, 0};
    };

    pos_s.push_back(gao(s));

    for (auto [op, k, c] : qry) {
        if (op == 2) {
            auto now = uptrie(*pos_s.rbegin(), k);
            // cout << op << " " << k << " " << now.first << " " << now.second
            //      << endl;
            pos_s.push_back(now);
            continue;
        }
        if (op == 3) {
            auto now = downtrie(*pos_s.rbegin(), k, c);
            // cout << op << " " << k << " " << c << " " << now.first << " "
            //      << now.second << endl;
            pos_s.push_back(now);
            continue;
        } else
            pos_s.push_back(*pos_s.rbegin());
    }

    for (int i = q - 1; i >= 0; i--) {
        auto [op, k, c] = qry[i];
        if (op == 1) {
            assert(segT.query(dfn[where[k - 1]], dfn[where[k - 1]], 1, ord,
                              1) >= 1);
            segT.add(dfn[where[k - 1]], -1, 1, ord, 1);
            segT.add(dfn[fa[where[k - 1]][0]], 1, 1, ord, 1);
            where[k - 1] = fa[where[k - 1]][0];
        } else {
            if (op == 4) {
                cerr << pos_s[i + 1].first << endl;
                cout << segT.query(1, dfn[pos_s[i + 1].first], 1, ord, 1)
                     << endl;
            }
        }
    }
    return 0;
}

/*
6 11
abe
aaa
aa
aab
aac
abd
bc
4
2 1
4
3 1 d
4
3 2 a
4
2 4
4
1 3 d
4
*/