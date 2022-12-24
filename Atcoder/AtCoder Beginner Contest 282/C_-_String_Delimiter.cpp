#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    int cnt = 0;

    string ans;
    for (int i = 0; i < n; i++) {
        char ch = s[i];
        if (s[i] == '"' && cnt == 1)
            cnt = 0;
        else if (s[i] == '"' && cnt == 0)
            cnt = 1;
        if (s[i] == ',' && cnt == 0) ch = '.';
        ans += ch;
    }

    for (auto p : ans) cout << p;
    return 0;
}