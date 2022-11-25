#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<string> lt;

    int n = s.size();
    for (int i = 0; i < n; i++) {
        string res =
            string{s.begin() + i, s.end()} + string{s.begin(), s.begin() + i};
        lt.push_back(res);
    }

    sort(lt.begin(), lt.end());

    cout << *lt.begin() << '\n' << lt.back();

    return 0;
}