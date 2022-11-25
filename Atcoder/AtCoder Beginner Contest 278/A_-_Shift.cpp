#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    deque<int> a;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    for (int i = 1; i <= k; i++) {
        a.pop_front();
        a.push_back(0);
    }

    for (auto p : a) cout << p << " ";
    return 0;
}