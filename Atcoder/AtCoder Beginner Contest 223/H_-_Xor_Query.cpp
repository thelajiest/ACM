#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int L = 20;
template <int L>
struct LinearBasis {
    array<i64, L + 1> a;
    LinearBasis() { a.fill(0); }

    void insert(long long t) {
        for (int j = L; j >= 0; j--) {
            if (!t) return;
            if (!(t & (1ll << j))) continue;

            if (a[j])
                t ^= a[j];
            else {
                for (int k = 0; k < j; k++)
                    if (t & (1ll << k)) t ^= a[k];
                for (int k = j + 1; k <= L; k++)
                    if (a[k] & (1ll << j)) a[k] ^= t;
                a[j] = t;
                break;
            }
        }
    }
};
using Lb = LinearBasis<L>;
/*
    O(nlog^2Aloglogn+qlogn)
*/
Lb op(const Lb &a, const Lb &b) {
    Lb res = a;
    for (int i = 0; i <= L; i++) res.insert(b.a[i]);
    return res;
}
class SqrtTree {
   private:
    int n, lg, indexSz;
    vector<Lb> v;
    vector<int> clz, layers, onLayer;
    vector<vector<Lb> > pref, suf, between;

    inline void buildBlock(int layer, int l, int r) {
        pref[layer][l] = v[l];
        for (int i = l + 1; i < r; i++) {
            pref[layer][i] = op(pref[layer][i - 1], v[i]);
        }
        suf[layer][r - 1] = v[r - 1];
        for (int i = r - 2; i >= l; i--) {
            suf[layer][i] = op(v[i], suf[layer][i + 1]);
        }
    }

    inline void buildBetween(int layer, int lBound, int rBound,
                             int betweenOffs) {
        int bSzLog = (layers[layer] + 1) >> 1;
        int bCntLog = layers[layer] >> 1;
        int bSz = 1 << bSzLog;
        int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;
        for (int i = 0; i < bCnt; i++) {
            Lb ans;
            for (int j = i; j < bCnt; j++) {
                Lb add = suf[layer][lBound + (j << bSzLog)];
                ans = (i == j) ? add : op(ans, add);
                between[layer - 1][betweenOffs + lBound + (i << bCntLog) + j] =
                    ans;
            }
        }
    }

    inline void buildBetweenZero() {
        int bSzLog = (lg + 1) >> 1;
        for (int i = 0; i < indexSz; i++) {
            v[n + i] = suf[0][i << bSzLog];
        }
        build(1, n, n + indexSz, (1 << lg) - n);
    }

    inline void updateBetweenZero(int bid) {
        int bSzLog = (lg + 1) >> 1;
        v[n + bid] = suf[0][bid << bSzLog];
        update(1, n, n + indexSz, (1 << lg) - n, n + bid);
    }

    void build(int layer, int lBound, int rBound, int betweenOffs) {
        if (layer >= (int)layers.size()) {
            return;
        }
        int bSz = 1 << ((layers[layer] + 1) >> 1);
        for (int l = lBound; l < rBound; l += bSz) {
            int r = min(l + bSz, rBound);
            buildBlock(layer, l, r);
            build(layer + 1, l, r, betweenOffs);
        }
        if (layer == 0) {
            buildBetweenZero();
        } else {
            buildBetween(layer, lBound, rBound, betweenOffs);
        }
    }

    void update(int layer, int lBound, int rBound, int betweenOffs, int x) {
        if (layer >= (int)layers.size()) {
            return;
        }
        int bSzLog = (layers[layer] + 1) >> 1;
        int bSz = 1 << bSzLog;
        int blockIdx = (x - lBound) >> bSzLog;
        int l = lBound + (blockIdx << bSzLog);
        int r = min(l + bSz, rBound);
        buildBlock(layer, l, r);
        if (layer == 0) {
            updateBetweenZero(blockIdx);
        } else {
            buildBetween(layer, lBound, rBound, betweenOffs);
        }
        update(layer + 1, l, r, betweenOffs, x);
    }

    inline Lb query(int l, int r, int betweenOffs, int base) {
        if (l == r) {
            return v[l];
        }
        if (l + 1 == r) {
            return op(v[l], v[r]);
        }
        int layer = onLayer[clz[(l - base) ^ (r - base)]];
        int bSzLog = (layers[layer] + 1) >> 1;
        int bCntLog = layers[layer] >> 1;
        int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
        int lBlock = ((l - lBound) >> bSzLog) + 1;
        int rBlock = ((r - lBound) >> bSzLog) - 1;
        Lb ans = suf[layer][l];
        if (lBlock <= rBlock) {
            Lb add = (layer == 0)
                         ? (query(n + lBlock, n + rBlock, (1 << lg) - n, n))
                         : (between[layer - 1][betweenOffs + lBound +
                                               (lBlock << bCntLog) + rBlock]);
            ans = op(ans, add);
        }
        ans = op(ans, pref[layer][r]);
        return ans;
    }

   public:
    inline Lb query(int l, int r) { return query(l, r, 0, 0); }

    inline void update(int x, const Lb &item) {
        v[x] = item;
        update(0, 0, n, 0, x);
    }

    SqrtTree(const vector<Lb> &a)
        : n((int)a.size()),
          lg(__lg(n) + 1),
          v(a),
          clz(1 << lg),
          onLayer(lg + 1) {
        clz[0] = 0;
        for (int i = 1; i < (int)clz.size(); i++) {
            clz[i] = clz[i >> 1] + 1;
        }
        int tlg = lg;
        while (tlg > 1) {
            onLayer[tlg] = (int)layers.size();
            layers.push_back(tlg);
            tlg = (tlg + 1) >> 1;
        }
        for (int i = lg - 1; i >= 0; i--) {
            onLayer[i] = max(onLayer[i], onLayer[i + 1]);
        }
        int betweenLayers = max(0, (int)layers.size() - 1);
        int bSzLog = (lg + 1) >> 1;
        int bSz = 1 << bSzLog;
        indexSz = (n + bSz - 1) >> bSzLog;
        v.resize(n + indexSz);
        pref.assign(layers.size(), vector<Lb>(n + indexSz));
        suf.assign(layers.size(), vector<Lb>(n + indexSz));
        between.assign(betweenLayers, vector<Lb>((1 << lg) + bSz));
        build(0, 0, n, 0);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<Lb> init(n);
    for (int i = 0; i < n; i++) {
        i64 x;
        cin >> x;
        init[i].insert(x);
    }

    SqrtTree t(init);

    while (q--) {
        int l, r;
        i64 x;
        cin >> l >> r >> x;
        l--, r--;
        auto qry = t.query(l, r);
        bool flag = true;
        for (int i = L; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (!qry.a[i]) {
                    flag = false;
                } else {
                    x ^= qry.a[i];
                }
            }
        }
        if (flag)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}