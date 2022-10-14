#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;

    bool ok = s.size() <= t.size();

    for (int i = 0; i < min(s.size(), t.size()); i++)
        if (s[i] != t[i]) ok = false;

    if (ok)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}