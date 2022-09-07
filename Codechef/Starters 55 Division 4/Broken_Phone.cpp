#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int _;
    cin >> _;

    while (_--) {
        i64 x, y;
        cin >> x >> y;
        if (x < y) puts("REPAIR");
        if (x > y) puts("NEW PHONE");
        if (x == y) puts("ANY");
    }

    return 0;
}