#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int pos = -1;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == 'a') pos = i + 1;
    cout << pos;

    return 0;
}