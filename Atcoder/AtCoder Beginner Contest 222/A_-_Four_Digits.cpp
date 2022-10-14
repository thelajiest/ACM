#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int len = s.size();
    len = 4 - len;
    string add;
    while (len--) add.push_back('0');

    s = add + s;
    cout << s;

    return 0;
}