#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> se;
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        se.insert(x);
    }

    cout << int(se.size()) << endl;

    return 0;
}