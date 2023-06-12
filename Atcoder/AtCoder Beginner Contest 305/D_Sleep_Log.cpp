#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<i64> A(n);
    for (int i = 0; i < n; i++) std::cin >> A[i];

    std::vector<i64> pre(n);
    for (int i = 0; i + 1 < n; i++) {
        pre[i + 1] = pre[i] + ((i & 1) ? (A[i + 1] - A[i]) : 0);
    }

    int Q;
    std::cin >> Q;

    return 0;
}