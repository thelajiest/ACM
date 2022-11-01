#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a(100);
    a[0] = 1;
    for (int i = 1; i <= 99; i++) {
        a[i] = a[i / 2] + a[i / 3];
    }
    for (auto it : a) {
        cerr << it << endl;
    }
    return 0;
}