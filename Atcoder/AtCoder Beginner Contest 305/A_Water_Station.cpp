#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    std::cin >> n;

    int L = n / 5 * 5;
    int R = (n + 4) / 5 * 5;

    if (n - L < R - n)
        std::cout << L;
    else
        std::cout << R;

    return 0;
}