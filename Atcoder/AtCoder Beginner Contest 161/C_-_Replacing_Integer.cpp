#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n, k;
    cin >> n >> k;

    cout << min(n % k, k - (n % k)) << '\n';

    return 0;
}