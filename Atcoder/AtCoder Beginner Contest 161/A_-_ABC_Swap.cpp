#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y, z;
    cin >> x >> y >> z;
    swap(x, y);
    swap(x, z);
    cout << x << " " << y << " " << z << endl;

    return 0;
}