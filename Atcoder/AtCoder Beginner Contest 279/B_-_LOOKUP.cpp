#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;

    cin >> s >> t;

    for (int i = 0; i < s.size(); i++) {
        bool ok = true;
        for (int j = 0; j < t.size(); j++)
            if (s[i + j] != t[j]) ok = false;
        if (ok) {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";
    return 0;
}