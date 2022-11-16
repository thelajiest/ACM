#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
map<string, int> mp = {{"-F", 1},         {"-Cl", 2},  {"-Br", 3},
                       {"-I", 4},         {"-CH3", 5}, {"-CH2CH3", 6},
                       {"-CH2CH2CH3", 7}, {"-H", 8}};
void solve() {
    string r1, r2, r3, r4;
    cin >> r1 >> r2 >> r3 >> r4;
    if (r1 == r3 || r2 == r4) {
        cout << "None";
        return;
    }
    if ((r1 == r2) || r3 == r4) {
        cout << "Cis";
        return;
    }
    if ((r1 == r4) || (r2 == r3)) {
        cout << "Trans";
        return;
    }
    if ((mp[r1] < mp[r3] && mp[r2] < mp[r4]) ||
        ((mp[r1] > mp[r3]) && mp[r2] > mp[r4]))
        cout << "Zasamman";
    else {
        cout << "Entgegen";
    }
    return;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
        cout << '\n';
    }
    return 0;
}