#include <bits/stdc++.h>

using i64 = std::int64_t;
using u32 = std::uint32_t;

struct Mo {
    int width;
    std::vector<int> left, right, order;
    int nl = 1, nr = 1;

    Mo(int N, int Q) : order(Q) {
        width = std::max<int>(
            1, 1.0 * N / std::max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
        std::iota(begin(order), end(order), 0);
    }

    void insert(int l, int r) { /* [l, r) */
        left.emplace_back(l);
        right.emplace_back(r);
    }

    template <typename AL, typename AR, typename DL, typename DR, typename REM>
    void run(const AL &add_left, const AR &add_right, const DL &delete_left,
             const DR &delete_right, const REM &rem) {
        assert(left.size() == order.size());
        std::sort(begin(order), end(order), [&](int a, int b) {
            int ablock = left[a] / width, bblock = left[b] / width;
            if (ablock != bblock) return ablock < bblock;
            if (ablock & 1) return right[a] < right[b];
            return right[a] > right[b];
        });
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

    Mo mo(N + 1, Q);
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