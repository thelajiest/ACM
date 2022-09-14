#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    if (s == "Monday") cout << 5;
    if (s == "Tuesday") cout << 4;
    if (s == "Wednesday") cout << 3;
    if (s == "Thursday") cout << 2;
    if (s == "Friday") cout << 1;

    return 0;
}