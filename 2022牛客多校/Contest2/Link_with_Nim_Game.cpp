#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef vector<int> VI;
typedef pair<int, int> pii;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<i64> a(n);
        for (auto& it : a) cin >> it;
        auto x = accumulate(a.begin(), a.end(), 0ll, bit_xor<i64>());
        auto y = accumulate(a.begin(), a.end(), 0ll, plus<i64>());
        if (x != 0) {
            map<i64, i64> mp;
            for (auto p : a) {
                if ((p ^ x) <= p) mp[p - (p ^ x)]++;
            }
            i64 mn = numeric_limits<i64>().min();
            for (auto [x, val] : mp) mn = max(mn, x);
            cout << y - mn + 1 << " " << mp[mn] << '\n';
        } else {
            i64 res = 0;
            map<i64, i64> mp;
            for (auto p : a) {
                if ((p >= (p ^ 1))) mp[p - (p ^ 1)]++;
            }
            i64 mn = numeric_limits<i64>().max();
            for (auto [x, val] : mp) mn = min(mn, x);
            // cerr << mn << endl;
            cout << y - mn + 1 << " " << mp[mn] << '\n';
        }
    }
}