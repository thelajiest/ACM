#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MOD = 998244353;

int n, tot;

bool chk_pri(int x) {
    if (x == 1) return false;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

signed main() {
    cin.sync_with_stdio(false);
    cin >> n;
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        tot += a;
    }
    if (n == 1) {
        if (chk_pri(tot)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else if (n == 2) {
        if (tot & 1) {
            if (tot <= 3) {
                cout << "No\n";
            } else {
                if (chk_pri(tot - 2)) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
            }
        } else {
            if (tot <= 2) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        }
    } else {
        if (tot & 1) {
            if (tot - (n - 2) * 2 - 1 <= 2) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        } else {
            if (tot - (n - 2) * 2 <= 2) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        }
    }
    return 0;
}