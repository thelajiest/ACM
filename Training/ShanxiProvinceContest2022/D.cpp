#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int mod = 6E6 - 7;

void solve() {
    srand(time(0));
    string s;
    cin >> s;
    int hxs = 0;
    for (char c : s) hxs = (hxs * 29 + (c - 'a' + 1)) % mod;
    constexpr int L = 3;
    int dut = 1;
    for (int i = 1; i <= L; i++) dut = dut * 29 % mod;
    int i = 0;
    while (true) {
        vector<char> res;
        int hxres = 0;
        for (int i = 0; i < L; i++) {
            res.emplace_back(char(rand() % 26 + 'a'));
            hxres = (hxres * 29 + (res.back() - 'a' + 1)) % mod;
        }
        if ((hxres + 1LL * hxs * dut % mod) % mod == hxs) {
            for (auto c : s) cout << c;
            for (auto c : res) cout << c;
            break;
        }
    }
    cout << '\n';
    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}