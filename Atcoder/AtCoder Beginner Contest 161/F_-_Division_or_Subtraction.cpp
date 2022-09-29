#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n;
    cin >> n;

    if (n == 2) {
        cout << 1 << endl;
        return 0;
    }

    vector<i64> div;

    for (i64 i = 2; i * i <= n; i++) {
        if (n % i == 0) div.push_back(i), div.push_back(n / i);
    }
    div.push_back(n);
    sort(begin(div), end(div));
    div.resize(unique(begin(div), end(div)) - begin(div));
    i64 ans = 0;
    for (auto p : div) {
        i64 now = n;
        while (now % p == 0) {
            now /= p;
        }
        if (now % p == 1) ans++;
    }
    div.clear();
    for (i64 i = 2; i * i <= n - 1; i++) {
        if ((n - 1) % i == 0) div.push_back(i), div.push_back((n - 1) / i);
    }
    div.push_back(n - 1);

    sort(begin(div), end(div));
    div.resize(unique(begin(div), end(div)) - begin(div));

    ans += div.size();

    cout << ans << endl;

    return 0;
}