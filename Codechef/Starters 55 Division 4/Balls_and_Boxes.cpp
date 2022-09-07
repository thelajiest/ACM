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
        i64 n, k;
        cin >> n >> k;
        i64 res = k * (1 + k) / 2;
        if (n >= res)
            puts("YES");
        else
            puts("NO");
    }

    return 0;
}