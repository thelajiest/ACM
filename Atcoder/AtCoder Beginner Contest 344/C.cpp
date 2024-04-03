#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M, L;
    std::vector<int> A, B, C;

    std::cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::cin >> M;
    B.resize(M);
    for (int i = 0; i < M; i++) {
        std::cin >> B[i];
    }

    std::cin >> L;
    C.resize(L);
    for (int i = 0; i < L; i++) {
        std::cin >> C[i];
    }

    std::set<int> S;
    for (auto x : B) {
        for (auto y : C) {
            S.insert(x + y);
        }
    }

    int Q;
    std::cin >> Q;
    for (int t = 0; t < Q; t++) {
        int x;
        std::cin >> x;
        bool find = false;

        for (auto i : A) {
            auto y = x - i;
            auto it = S.find(y);
            if (it == S.end()) continue;
            find = true;
            break;
        }

        if (find) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}