#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> s(m, vector<char>(n)), t(m, vector<char>(n));

    for (int i = 0; i < n; i++) {
        string res;
        cin >> res;
        for (int j = 0; j < m; j++) s[j][i] = res[j];
    }

    for (int i = 0; i < n; i++) {
        string res;
        cin >> res;
        for (int j = 0; j < m; j++) t[j][i] = res[j];
    }
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    for (int i = 0; i < m; i++) {
        if (s[i] != t[i]) {
            cout << "No";
            return 0;
        }
    }

    cout << "Yes";

    return 0;
}