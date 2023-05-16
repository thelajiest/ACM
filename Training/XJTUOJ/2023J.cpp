#include <bits/stdc++.h>

using i64 = std::int64_t;
using u32 = std::uint32_t;

struct Fast_Mo {
    int N, Q, width;
    std::vector<int> left, right, order;
    bool is_build;
    int nl = 1, nr = 1;

    Fast_Mo(int _n, int _q) : N(_n), Q(_q), order(Q), is_build(false) {
        width =
            std::max<int>(1, 1.0 * N / std::max<double>(1.0, sqrt(Q / 2.0)));
        std::iota(begin(order), end(order), 0);
    }
    // [l, r)
    void insert(int l, int r) {
        assert(0 <= l and l <= r and r <= N);
        left.push_back(l), right.push_back(r);
    }

    void build() { sort(), climb(), is_build = true; }

    template <typename AL, typename AR, typename DL, typename DR, typename REM>
    void run(const AL &add_left, const AR &add_right, const DL &delete_left,
             const DR &delete_right, const REM &rem) {
        if (!is_build) build();
        for (auto idx : order) {
            while (nl > left[idx]) {
                nl--;
                add_left(nl);
            }
            while (nr < right[idx]) {
                nr++;
                add_right(nr - 1);
            }
            while (nl < left[idx]) {
                nl++;
                delete_left(nl - 1);
            }
            while (nr > right[idx]) {
                nr--;
                delete_right(nr);
            }
            rem(idx);
        }
    }

   private:
    void sort() {
        assert((int)order.size() == Q);
        std::vector<int> cnt(N + 1), buf(Q);
        for (int i = 0; i < Q; i++) cnt[right[i]]++;
        for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < Q; i++) buf[--cnt[right[i]]] = i;
        std::vector<int> b(Q);
        for (int i = 0; i < Q; i++) b[i] = left[i] / width;
        cnt.resize(N / width + 1);
        std::fill(begin(cnt), end(cnt), 0);
        for (int i = 0; i < Q; i++) cnt[b[i]]++;
        for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < Q; i++) order[--cnt[b[buf[i]]]] = buf[i];
        for (int i = 0, j = 0; i < Q; i = j) {
            int bi = b[order[i]];
            j = i + 1;
            while (j != Q and bi == b[order[j]]) j++;
            if (!(bi & 1)) std::reverse(begin(order) + i, begin(order) + j);
        }
    }

    int dist(int i, int j) {
        return abs(left[i] - left[j]) + abs(right[i] - right[j]);
    }

    void climb(int iter = 3, int interval = 5) {
        std::vector<int> d(Q - 1);
        for (int i = 0; i < Q - 1; i++) d[i] = dist(order[i], order[i + 1]);
        while (iter--) {
            for (int i = 1; i < Q; i++) {
                int pre1 = d[i - 1];
                int js = i + 1, je = std::min<int>(i + interval, Q - 1);
                for (int j = je - 1; j >= js; j--) {
                    int pre2 = d[j];
                    int now1 = dist(order[i - 1], order[j]);
                    int now2 = dist(order[i], order[j + 1]);
                    if (now1 + now2 < pre1 + pre2) {
                        std::reverse(begin(order) + i, begin(order) + j + 1);
                        std::reverse(begin(d) + i, begin(d) + j);
                        d[i - 1] = pre1 = now1;
                        d[j] = now2;
                    }
                }
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<u32> a(N + 1);
    for (int i = 1; i <= N; i++) std::cin >> a[i];

    std::vector<int> leftPos(N + 1), rightPos(N + 1);
    std::vector<int> mpPos(N + 1);

    for (int i = 1; i <= N; i++) {
        leftPos[i] = mpPos[a[i]];
        mpPos[a[i]] = i;
    }

    std::fill(begin(mpPos), end(mpPos), N + 1);
    for (int i = N; i >= 1; i--) {
        rightPos[i] = mpPos[a[i]];
        mpPos[a[i]] = i;
    }

    u32 curAns = 0;
    u32 leftAns = 0, rightAns = 0;
    u32 interCnt = 0;
    std::vector<u32> ans(Q);

    Fast_Mo mo(N + 1, Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        std::cin >> l >> r;
        r++;
        mo.insert(l, r);
    }

    auto addleft = [&](int idx) {
        auto last = rightPos[idx];
        if (last >= mo.nr) {
            curAns += u32(mo.nr - mo.nl) + leftAns;
            interCnt++;
            leftAns += u32(mo.nr - mo.nl);
            rightAns += interCnt;
        } else {
            curAns += u32(last - mo.nl) + leftAns;
            leftAns += u32(last - mo.nl);
            rightAns += interCnt;
        }
    };
    auto addright = [&](int idx) {
        auto last = leftPos[idx];
        if (last < mo.nl) {
            curAns += u32(mo.nr - mo.nl) + rightAns;
            interCnt++;
            rightAns += u32(mo.nr - mo.nl);
            leftAns += interCnt;

        } else {
            curAns += u32(mo.nr - (last + 1)) + rightAns;
            rightAns += u32(mo.nr - (last + 1));
            leftAns += interCnt;
        }
    };
    auto delleft = [&](int idx) {
        auto last = rightPos[idx];
        if (last >= mo.nr) {
            leftAns -= u32(mo.nr - (mo.nl - 1));
            rightAns -= interCnt;
            interCnt--;
            curAns -= (u32(mo.nr - (mo.nl - 1)) + leftAns);
        } else {
            leftAns -= u32(last - (mo.nl - 1));
            rightAns -= interCnt;
            curAns -= (u32(last - (mo.nl - 1)) + leftAns);
        }
    };
    auto delright = [&](int idx) {
        auto last = leftPos[idx];
        if (last < mo.nl) {
            rightAns -= u32(mo.nr + 1 - mo.nl);
            leftAns -= interCnt;
            interCnt--;
            curAns -= (u32(mo.nr + 1 - mo.nl) + rightAns);
        } else {
            rightAns -= u32(mo.nr - last);
            leftAns -= interCnt;
            curAns -= (u32(mo.nr - last) + rightAns);
        }
    };
    auto rem = [&](int idx) { ans[idx] = curAns; };
    mo.run(addleft, addright, delleft, delright, rem);

    for (int i = 0; i < Q; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}