#include <bits/stdc++.h>

using i64 = std::int64_t;
using u32 = std::uint32_t;

template <class Weight, class PosX, class PosY>
struct StaticRectangleAddRectangleSum {
   public:
    struct Rectangle {
        PosX l, r;  // l < r
        PosY t, b;  // t < b
    };
    struct Weight2 {
        Weight a = 0, b = 0;
        Weight2& operator+=(Weight2 r) {
            a += r.a;
            b += r.b;
            return *this;
        }
        Weight2& operator-=(Weight2 r) {
            a -= r.a;
            b -= r.b;
            return *this;
        }
        Weight2 operator*(Weight r) const { return {a * r, b * r}; }
    };
    struct A {
        Weight2 a, b;
        A& operator+=(A r) {
            a += r.a;
            b += r.b;
            return *this;
        }
        A& operator-=(A r) {
            a -= r.a;
            b -= r.b;
            return *this;
        }
    };

   private:
    std::vector<A> bit;
    std::vector<PosX> posX;
    struct UpdateQuery {
        PosY y;
        int l;
        int r;
        Weight w;
    };
    int compressX(const PosX& x) {
        return std::lower_bound(posX.begin(), posX.end(), x) - posX.begin();
    }
    std::vector<UpdateQuery> updQueries;
    Weight2 bitQuery(PosX x) {
        int p = compressX(x);
        A res = {Weight2(), Weight2()};
        while (p) {
            res += bit[p - 1];
            p -= p & -p;
        }
        return res.b += res.a * Weight(x);
    }
    Weight2 bitQuery(PosX l, PosX r) { return bitQuery(r) -= bitQuery(l); }
    void bitAdd(int p, Weight2 val) {
        A x = {val, val * -Weight(posX[p])};
        p++;
        while (p <= (int)bit.size()) {
            bit[p - 1] += x;
            p += p & -p;
        }
    }

   public:
    using InputType = std::vector<std::pair<Rectangle, Weight>>;
    using QueryInputType = std::vector<Rectangle>;
    StaticRectangleAddRectangleSum(
        const std::vector<std::pair<Rectangle, Weight>>& rects = {}) {
        for (auto& e : rects) {
            posX.push_back(e.first.l);
            posX.push_back(e.first.r);
        }
        std::sort(posX.begin(), posX.end());
        posX.erase(std::unique(posX.begin(), posX.end()), posX.end());
        for (auto& e : rects) {
            int l = compressX(e.first.l), r = compressX(e.first.r);
            updQueries.push_back({e.first.t, l, r, e.second});
            updQueries.push_back({e.first.b, l, r, -e.second});
        }
        std::sort(updQueries.begin(), updQueries.end(),
                  [](const UpdateQuery& l, const UpdateQuery& r) {
                      return l.y < r.y;
                  });
    }
    std::vector<Weight> query(const std::vector<Rectangle>& ranges) {
        bit.assign(posX.size(), A{});
        struct HQ {
            PosY y;
            int i;
            int way;
        };
        std::vector<HQ> hq;
        for (int i = 0; i < (int)ranges.size(); i++) {
            hq.push_back({ranges[i].t, i, 0});
            hq.push_back({ranges[i].b, i, 1});
        }
        std::sort(hq.begin(), hq.end(),
                  [](const HQ& l, const HQ& r) { return l.y < r.y; });
        auto upd = updQueries.begin();
        std::vector<Weight> res(ranges.size());
        int i = 0;
        for (auto& q : hq) {
            while (upd != updQueries.end() && upd->y < q.y) {
                Weight wy = Weight(upd->y);
                bitAdd(upd->l, {upd->w, -upd->w * wy});
                bitAdd(upd->r, {-upd->w, upd->w * wy});
                upd++;
            }
            auto v = bitQuery(ranges[q.i].l, ranges[q.i].r);
            if (q.way == 1) res[q.i] += v.a * Weight(q.y) + v.b;
            if (q.way == 0) res[q.i] -= v.a * Weight(q.y) + v.b;
            i++;
        }
        return res;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<u32> a(N + 1);
    for (int i = 1; i <= N; i++) std::cin >> a[i];

    std::vector<int> leftPos(N + 1);
    std::vector<int> mpPos(N + 1);

    for (int i = 1; i <= N; i++) {
        leftPos[i] = mpPos[a[i]];
        mpPos[a[i]] = i;
    }

    using solve = StaticRectangleAddRectangleSum<u32, int, int>;
    solve::InputType update(N);
    solve::QueryInputType qry(Q);

    for (int i = 1; i <= N; i++) {
        int lmin = leftPos[i] + 1;
        int lmax = i;
        int rmin = i;
        int rmax = N;
        auto& a = update[i - 1];
        a.first.l = lmin;
        a.first.t = rmin;
        a.first.r = lmax + 1;
        a.first.b = rmax + 1;
        a.second = 1;
    }

    for (int i = 0; i < Q; i++) {
        int l, r;
        std::cin >> l >> r;
        auto& a = qry[i];
        a.l = l;
        a.t = l;
        a.r = r + 1;
        a.b = r + 1;
    }
    auto res = solve(update).query(qry);
    for (auto ans : res) {
        std::cout << ans << '\n';
    }

    return 0;
}