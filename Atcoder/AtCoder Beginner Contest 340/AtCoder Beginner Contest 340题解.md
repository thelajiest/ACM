# AtCoder Beginner Contest 340题解

## A - Arithmetic Progression

循环模拟即可。

```cpp
#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int A, B, D;
    std::cin >> A >> B >> D;

    for (int i = A; i <= B; i += D) {
        std::cout << i << " ";
    }

    return 0;
}
```

## B - Append

用`vector`模拟即可。

```cpp
#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Q;
    std::cin >> Q;

    std::vector<int> a;
    while (Q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int x;
            std::cin >> x;
            a.push_back(x);
        } else {
            int k;
            std::cin >> k;
            int size = std::size(a);

            std::cout << a[size - k] << '\n';
        }
    }

    return 0;
}
```

## C - Divide and Divide

$f(n) = f(\frac{n}{2}) + f(\frac{n+1}{2}) + n$，直接记忆化搜索，时间复杂度为$\mathcal{O}(\log{N})$。

```cpp
#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 N;
    std::cin >> N;
    std::map<i64, i64> sum;
    auto dfs = [&](auto&& self, i64 now) -> i64 {
        if (sum.count(now)) return sum[now];
        i64 ans = now;
        i64 low = now / 2;
        i64 high = (now + 1) / 2;
        if (low >= 2 && high == low) ans += 2 * self(self, low);
        if (low >= 2 && high != low) ans += self(self, high) + self(self, low);
        if (low == 1 && high != 1) ans += self(self, high);

        return sum[now] = ans;
    };

    std::cout << dfs(dfs, N) << std::endl;

    return 0;
}
```

## D - Super Takahashi Bros

按照题意建图，问题等价为求最短路，使用Dikjstra算法即可。

```cpp
#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<std::vector<std::pair<int, i64>>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        i64 A, B;
        int X;
        std::cin >> A >> B >> X;
        X--;
        adj[i].emplace_back(i + 1, A);
        adj[i].emplace_back(X, B);
    }

    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>,
                        std::greater<std::pair<i64, int>>>
        Q;

    std::vector<i64> dis(N, 1E18);
    std::vector<int> vis(N);

    Q.push({0, 0});
    dis[0] = 0;
    while (!Q.empty()) {
        auto [d, x] = Q.top();
        Q.pop();
        if (vis[x]) continue;
        vis[x] = 1;

        for (auto [y, w] : adj[x]) {
            if (dis[x] + w < dis[y]) {
                dis[y] = dis[x] + w;
                Q.push({dis[y], y});
            }
        }
    }

    std::cout << dis.back() << std::endl;
    return 0;
}
```

## E - Mancala 2

每次操作一定是末尾和开头的连续段$+1$以及若干整段的$+1$操作，这些操作都可以用一个加法懒标记的线段树维护。

```cpp
#include <bits/stdc++.h>
using i64 = std::int64_t;

template <class Info, class Tag>
struct LazySegmentTree {
    /*
        Info: apply,operator +
        Tag: apply
        all operations obey [l,r)
    */
    const int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n)
        : n(n), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) { modify(1, 0, n, p, v); }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) +
               rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
};

struct Tag {
    i64 x = 0;
    void apply(const Tag &a) { x = x + a.x; }
};

struct Info {
    i64 x = 0;
    int l, r;
    void apply(const Tag &a) { x += 1LL * (r - l) * a.x; }
};
Info operator+(const Info &a, const Info &b) { return {a.x + b.x, a.l, b.r}; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    std::vector<Info> init(N);

    for (int i = 0; i < N; i++) {
        i64 x;
        std::cin >> x;
        init[i] = {x, i, i + 1};
    }

    LazySegmentTree<Info, Tag> sgtree(init);

    for (int i = 0; i < M; i++) {
        int b;
        std::cin >> b;

        auto cnt = sgtree.rangeQuery(b, b + 1).x;
        sgtree.rangeApply(b, b + 1, {-cnt});
        if (N - (b + 1) > cnt) {
            sgtree.rangeApply(b + 1, b + 1 + cnt, {1});
            continue;
        } else {
            sgtree.rangeApply(b + 1, N, {1});
        }
        cnt -= (N - (b + 1));
        auto left = cnt % N;
        auto full = cnt / N;

        sgtree.rangeApply(0, N, {full});
        if (left != 0) {
            sgtree.rangeApply(0, left, {1});
        }
    }

    for (int i = 0; i < N; i++) {
        std::cout << sgtree.rangeQuery(i, i + 1).x << " \n"[i == N - 1];
    }

    return 0;
}
```

## F - S = 1

即求$A,B$使得$|AY - BX| = 2$，这是一个经典的同余方程，使用拓展欧几里得算法求解。

```cpp
#include <bits/stdc++.h>
using i64 = std::int64_t;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    auto res = exgcd(b, a % b, x, y);
    i64 t = x;
    x = y;
    y = t - a / b * y;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 X, Y;
    std::cin >> X >> Y;

    std::swap(X, Y);
    i64 A = 0, B = 0;

    auto d = exgcd(abs(X), abs(Y), A, B);
    if (X < 0) A = -A;
    if (Y > 0) B = -B;

    if (2 % d != 0) {
        std::cout << "-1" << std::endl;
    } else {
        A = A * (2 / d);
        B = B * (2 / d);
        std::cout << A << " " << B << std::endl;
    }
    return 0;
}
```

、
