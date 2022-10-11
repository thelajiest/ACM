#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<i64> a(n);
    for (auto&& it : a) cin >> it;
    auto sum = accumulate(a.begin(), a.end(), 0LL);

    cout << sum;
    return 0;
}