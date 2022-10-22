#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char s, t;
    cin >> s >> t;
    if (s == 'Y') {
        cout << char(t + 'A' - 'a');
    } else
        cout << t;
    return 0;
}