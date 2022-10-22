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
    constexpr int N = 2E5;
    vector<int> cnt(N + 1);
    int p = 0;
    for (int i = 0; i < n; i++) {
        cnt[a[i]] = 1;
        if (a[i] >= p) {
            while (cnt[p] == 1) p++;
            ;
        }
        cout << p << '\n';
    }
    return 0;
}