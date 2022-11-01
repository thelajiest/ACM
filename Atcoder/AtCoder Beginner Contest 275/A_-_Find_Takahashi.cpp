#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& it : a) cin >> it;
    if (n == 1) {
        cout << 1;
        return 0;
    }
    cout << max_element(begin(a), end(a)) - begin(a) + 1;
    return 0;
}