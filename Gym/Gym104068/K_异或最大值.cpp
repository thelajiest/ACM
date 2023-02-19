#include <bits/stdc++.h>

using i64 = std::int64_t;

struct Node {
    Node() : lson(nullptr), rson(nullptr), sum(0){};
    Node* lson;
    Node* rson;
    int sum;
};

Node* insert(int x, Node* last) {
    auto rt = new Node();
    auto p = rt;
    for (int i = 30; i >= 0; i--) {
        if (last) p->lson = last->lson;
        if (last) p->rson = last->rson;

        int j = ((x >> i) & 1);
        if (j == 0) {
            p->lson = new Node();
            p = p->lson;
            if (last) last = last->lson;
            if (last)
                p->sum = last->sum + 1;
            else
                p->sum = 1;
        } else {
            p->rson = new Node();
            p = p->rson;
            if (last) last = last->rson;
            if (last)
                p->sum = last->sum + 1;
            else
                p->sum = 1;
        }
    }
    return rt;
};

int query(int x, int amax, Node* l, Node* r) {
    // x ^ a[L,R] > amax
    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        int amaxj = ((amax >> i) & 1);
        int xj = ((x >> i) & 1);

        if (amaxj == 1 && xj == 0) {
            if (l) l = l->rson;
            if (r) r = r->rson;
        }
        if (amaxj == 1 && xj == 1) {
            if (l) l = l->lson;
            if (r) r = r->lson;
        }
        if (amaxj == 0 && xj == 0) {
            if ((r != nullptr) && (r->rson != nullptr)) ans += (r->rson->sum);
            if ((l != nullptr) && (l->rson != nullptr)) ans -= (l->rson->sum);
            if (l) l = l->lson;
            if (r) r = r->lson;
        }
        if (amaxj == 0 && xj == 1) {
            if ((r != nullptr) && (r->lson != nullptr)) ans += (r->lson->sum);
            if ((l != nullptr) && (l->lson != nullptr)) ans -= (l->lson->sum);

            if (l) l = l->rson;
            if (r) r = r->rson;
        }
    }

    return ans;
}

template <typename Info>
struct SegmentTree {
    int N;
    int size;
    std::vector<Info> seg;

    SegmentTree(int _N) { init(_N); }

    //[0,v.size)
    SegmentTree(const std::vector<Info>& v) {
        init(v.size());
        for (int i = 0; i < (int)v.size(); i++) {
            seg[i + size] = v[i];
        }
        build();
    }
    void init(int _N) {
        N = _N;
        size = 1;
        while (size < N) size <<= 1;
        seg.assign(2 * size, Info());
    }
    void set(int k, const Info& x) { seg[k + size] = x; }
    void build() {
        for (int k = size - 1; k > 0; k--) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void update(int k, const Info& x) {
        k += size;
        seg[k] = x;
        while (k >>= 1) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void add(int k, const Info& x) {
        k += size;
        seg[k] += x;
        while (k >>= 1) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    // query to [a, b)
    Info query(int a, int b) {
        Info L = Info(), R = Info();
        for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) L = L + seg[a++];
            if (b & 1) R = seg[--b] + R;
        }
        return L + R;
    }
    Info& operator[](const int& k) { return seg[k + size]; }
};

struct Info {
    int x = 0;
    int pos = -1;
    Info& operator+=(const Info& a) {
        if (x < a.x) {
            x = a.x;
            pos = a.pos;
        }
        return *this;
    }
};
Info operator+(const Info& a, const Info& b) {
    if (a.pos == -1) return b;
    if (b.pos == -1) return a;
    if (a.x > b.x) {
        return {a.x, a.pos};
    }
    return {b.x, b.pos};
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    std::vector<Info> _init(n + 1);
    for (int i = 0; i <= n; i++) {
        _init[i] = {a[i], i};
    }

    SegmentTree<Info> ST(_init);
    std::vector<Node*> Trie(n + 1);
    Trie[0] = new Node();

    for (int i = 1; i <= n; i++) {
        Trie[i] = insert(a[i], Trie[i - 1]);
    }

    i64 ans = 0;
    auto dfs = [&](auto&& self, int l, int r) -> void {
        if (l >= r) return;
        auto [amax, pos] = ST.query(l, r + 1);
        if (pos - l < r - pos) {
            for (int i = l; i <= pos; i++) {
                ans += query(a[i], amax, Trie[pos - 1], Trie[r]);
            }
        } else {
            for (int i = pos; i <= r; i++) {
                ans += query(a[i], amax, Trie[l - 1], Trie[pos]);
            }
        }
        self(self, l, pos - 1);
        self(self, pos + 1, r);
    };

    dfs(dfs, 1, n);

    std::cout << ans << std::endl;
    return 0;
}