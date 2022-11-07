#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

vector<vector<char>> rotate(vector<vector<char>> a) {
    int n = a.size();
    vector<vector<char>> ans(n, vector<char>(n));
    int now = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            int nowx = now / n;
            int nowy = now % n;
            ans[j][i] = a[nowx][nowy];
            now++;
        }
    }
    return ans;
}
vector<vector<char>> hmirro(vector<vector<char>> a) {
    int n = a.size();
    vector<vector<char>> ans(n, vector<char>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) ans[n - i - 1][j] = a[i][j];
    }
    return ans;
}
vector<vector<char>> vmirro(vector<vector<char>> a) {
    int n = a.size();
    vector<vector<char>> ans(n, vector<char>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) ans[i][n - j - 1] = a[i][j];
    }
    return ans;
}

bool issame(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (a[i][j] != b[i][j]) return false;
    }
    return true;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<char>> a(n), b(n);
    for (int i = 0; i < n; i++) {
        string res;
        cin >> res;
        a[i] = {res.begin(), res.end()};
    }
    for (int i = 0; i < n; i++) {
        string res;
        cin >> res;
        b[i] = {res.begin(), res.end()};
    }

    bool ok = false;
    if (issame(a, b)) {
        cout << "YES";
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        a = rotate(a);
        auto h = hmirro(a);
        auto v = vmirro(a);

        if (issame(a, b) || issame(h, b) || issame(v, b)) ok = true;
    }

    if (ok)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}