#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 7;
const int MAX_M = 4e3 + 7;
bitset<MAX_M> bit, now;
char s[MAX_M];
int n, m, q;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    bit.reset();
    for (int i = 0; i < m; ++i) bit.set(i);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        now.reset();
        for (int j = 0; j < m; ++j) {
            if (s[j] == '1') {
                now.set(j);
            }
        }
        bit &= now;
    }
    cin >> q;
    while (q--) {
        int i, j, l, r, p;
        cin >> i >> j >> l >> r >> p;
    }
    cout << bit.count() << "\n";
    return 0;
}