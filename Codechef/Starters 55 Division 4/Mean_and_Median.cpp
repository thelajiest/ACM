#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int _;
    cin >> _;

    while (_--) {
        int a, b;
        cin >> a >> b;
        for (int x = -300; x <= b; x++) {
            int z = 3 * a - x - b;
            if (z >= b) {
                cout << x << " " << b << " " << z << '\n';
                assert(3 * a == x + b + z);
                break;
            }
        }
    }

    return 0;
}