#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 2 || n == 4)
        cout << -1;
    else {
        if (n % 2 == 0) {
            int now = n / 2;
            cout << now << endl;
            for (int i = 0; i <= now; i++)
                if (i != 1) cout << i << " ";
        } else {
            int now = n / 2;
            cout << now + 1 << endl;
            for (int i = 0; i <= now; i++) cout << i << " ";
        }
    }

    return 0;
}