#include <bits/stdc++.h>

using i64 = std::int64_t;
template <typename T>
struct BinaryIndexedTree {
    int N;
    std::vector<T> data;
    BinaryIndexedTree() = default;
    BinaryIndexedTree(int size) { init(size); }
    void init(int size) {
        N = size + 2;
        data.assign(N + 1, {});
    }
    T sum(int k) const {
        if (k < 0) return T{};  // return 0 if k < 0
        T ret{};
        for (++k; k > 0; k -= k & -k) ret += data[k];
        return ret;
    }
    inline T sum(int l, int r) const { return sum(r) - sum(l - 1); }
    inline T operator[](int k) const { return sum(k) - sum(k - 1); }
    void add(int k, T x) {
        for (++k; k < N; k += k & -k) data[k] += x;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector a(n, std::vector(m, 0));
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
            v.push_back(a[i][j]);
        }
    }

    std::sort(begin(v), end(v));
    v.resize(std::unique(begin(v), end(v)) - v.begin());

    BinaryIndexedTree<int> Bit(v.size());
    i64 ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            int x = std::lower_bound(begin(v), end(v), a[i][j]) - v.begin();
            ans += Bit.sum(x);
        }
        ans += 1LL * m * (m + 1) / 2 * (n - 1 - i);
        for (int j = 0; j < m; j++) {
            int x = std::lower_bound(begin(v), end(v), a[i][j]) - v.begin();
            Bit.add(x, 1);
        }
    }

    std::cout << ans << std::endl;

    return 0;
}