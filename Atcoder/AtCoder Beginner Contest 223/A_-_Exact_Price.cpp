#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    cin >> x;
    cout << (((x % 100 == 0) && (x != 0)) ? "Yes" : "No");
    return 0;
}