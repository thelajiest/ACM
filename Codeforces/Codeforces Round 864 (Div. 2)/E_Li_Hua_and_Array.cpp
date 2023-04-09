#include <bits/stdc++.h>

using i64 = std::int64_t;

template <typename Info>
struct SegmentTree {
    int N;
    int size;
    std::vector<Info> seg;

    SegmentTree(int _N) { init(_N); }

    //[0,v.size)
    SegmentTree(const std::vector<Info> &v) {
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
    void set(int k, const Info &x) { seg[k + size] = x; }
    void build() {
        for (int k = size - 1; k > 0; k--) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void update(int k, const Info &x) {
        k += size;
        seg[k] = x;
        while (k >>= 1) {
            seg[k] = seg[2 * k] + seg[2 * k + 1];
        }
    }
    void add(int k, const Info &x) {
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
    Info &operator[](const int &k) { return seg[k + size]; }
};

struct Info {
    int max = std::numeric_limits<int>::min() / 3.0;
    int min = std::numeric_limits<int>::max() / 3.0;
};
Info operator+(const Info &a, const Info &b) {
    return {std::max(a.max, b.max), std::min(a.min, b.min)};
}

std::vector<int> prime_sieve(int N) {
    std::vector<bool> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    std::vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}

template <class T>
std::vector<T> mf_sieve(int n, std::function<T(i64, i64, i64)> f) {
    /*
        ##pragma f is a multiplicative-function
        f(n,p,c) <-> n=p^c
    */
    std::vector<T> ans(n + 1, T());
    std::vector<int> ps = prime_sieve(n);
    int p(ps.size());

    std::function<void(int, i64, T)> dfs = [&](int i, i64 x, T y) {
        ans[x] = y;
        if (y == T()) return;
        for (int j = i + 1; j < p; j++) {
            i64 nx = x * ps[j];
            i64 dx = ps[j];
            if (nx > n) break;
            for (int c = 1; nx <= n; nx *= ps[j], dx *= ps[j], ++c)
                dfs(j, nx, y * f(dx, ps[j], c));
        }
    };
    ans[1] = 1;
    dfs(-1, 1, 1);
    return ans;
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    int maxPhiCnt = 0;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int sz = *(std::max_element(begin(a), end(a)));

    auto phi =
        mf_sieve<int>(sz + 1, [&](int n, int p, int c) { return n - n / p; });

    for (auto p : a) {
        auto solveTime = [&](int x) -> int {
            int ret = 0;
            while (x != 1) {
                x = phi[x];
                ret++;
            }
            return ret;
        };
        maxPhiCnt = std::max(maxPhiCnt, solveTime(p));
    }

    std::vector<SegmentTree<Info>> ST(maxPhiCnt + 1, n);

    for (int i = 0; i < n; i++) {
        int cur = a[i];
        for (int j = 0; j <= maxPhiCnt; j++) {
            ST[j].update(i, {cur, cur});
            cur = phi[cur];
        }
    }

     return 0;
}