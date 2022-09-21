#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int l = 1, r = n;

    while (l < r) {
        int mid = (l + r) / 2;
        cout << "? " << 1 << " " << n << " " << l << " " << mid << endl;
        cout.flush();
        int ans;
        cin >> ans;
        if (ans < (mid - l + 1))
            r = mid;
        else
            l = mid + 1;
    }

    int ans1 = l;

    l = 1, r = n;

    while (l < r) {
        int mid = (l + r) / 2;
        cout << "? " << l << " " << mid << " " << 1 << " " << n << endl;
        cout.flush();
        int ans;
        cin >> ans;
        if (ans < (mid - l + 1))
            r = mid;
        else
            l = mid + 1;
    }

    int ans2 = r;

    cout << "! " << ans2 << " " << ans1;

    return 0;
}