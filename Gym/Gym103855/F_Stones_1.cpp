#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.emplace_back(x);
    }
    a[0] = 0, a[n - 1] = 0;
    vector<int> d;
    for (int i = 0, j; i < n; i = j) {
        j = i;
        int mx = 0;
        while (s[i] == s[j] && j < n) {
            mx = max(mx, a[j]);
            j++;
        }
        d.push_back(mx);
    }
    int sz = d.size();
    if (d.size() <= 2) {
        cout << 0;
        return 0;
    }
    d.pop_back();
    reverse(begin(d), end(d));
    d.pop_back();
    // for (auto p : d) cerr << p << " ";
    sort(begin(d), end(d), greater<int>());

    int bound = (sz - 1) / 2;
    i64 sum = 0;
    for (int i = 0; i < bound; i++) sum += d[i];
    cout << sum;

    return 0;
}