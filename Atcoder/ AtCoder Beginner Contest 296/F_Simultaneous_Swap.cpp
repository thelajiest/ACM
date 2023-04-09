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

    // get sum of [0,k]
    T sum(int k) const {
        if (k < 0) return T{};  // return 0 if k < 0
        T ret{};
        for (++k; k > 0; k -= k & -k) ret += data[k];
        return ret;
    }

    // getsum of [l,r]
    inline T sum(int l, int r) const { return sum(r) - sum(l - 1); }

    // get value of k
    inline T operator[](int k) const { return sum(k) - sum(k - 1); }

    // data[k] += x
    void add(int k, T x) {
        for (++k; k < N; k += k & -k) data[k] += x;
    }
};

i64 countInverseNumber(const std::vector<int>& a, int n) {
    BinaryIndexedTree<i64> bit(n + 1);

    i64 ret = 0;
    for (auto curNum : a) {
        ret += bit.sum(curNum - 1);
        bit.add(curNum, 1);
    }

    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::map<int, int> mpa, mpb;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        mpa[a[i]]++;
    }

    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        mpb[b[i]]++;
    }

    for (const auto& [x, cntx] : mpa) {
        if (mpb[x] != cntx) {
            std::cout << "No";
            return 0;
        }
    }

    for (const auto& [x, cntx] : mpa) {
        if (cntx > 1 || mpb[x] > 1) {
            std::cout << "Yes";
            return 0;
        }
    }

    auto invA = countInverseNumber(a, n);
    auto invB = countInverseNumber(b, n);

    if ((invA + invB) % 2 == 0) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }

    return 0;
}