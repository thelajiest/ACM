#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> mp;
    string s;
    while (cin >> s) mp.push_back(s);

    vector<pair<int, int>> res;

    for (int i = 0; i < int(mp.size()); i++)
        for (int j = 0; j < int(mp.size()); j++)
            if (mp[i][j] == '#') res.emplace_back(i, j);

    sort(begin(res), end(res));

    int a = res.begin()->first;
    int b = res.rbegin()->first;
    int c = res.begin()->second;
    int d = res.rbegin()->second;

    cout << a + 1 << " " << b + 1 << endl << c + 1 << " " << d + 1 << endl;

    return 0;
}