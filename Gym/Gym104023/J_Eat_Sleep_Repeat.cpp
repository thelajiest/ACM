#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 1E5 + 100;
using pii = pair<int, int>;

int T, n, k;
int a[MAX_N];
pii b[MAX_N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int j = 0; j < k; ++j) {
            cin >> b[j].first >> b[j].second;
        }
        sort(a, a + n);
        b[k].first = -1, b[k].second = 0, k += 1;
        b[k].first = a[n - 1] + 1, b[k].second = 0, k += 1;
        sort(b, b + k);
        // init

        int ans = 0;
        int beg = -2, lst = -1;
        list<int> x;
        for (int i = 0, j = 0; i < k; ++i) {
            if (0 == b[i].second) {
                // TODO:
                x.push_back(n);
                for (; j < n && beg <= a[j] && a[j] < b[i].first; ++j) {
                    ans += a[j] - beg;
                    // cerr << '!' << beg << ':' << a[j] << endl;
                    if (0 == --*x.begin()) {
                        x.pop_front();
                        beg += 1;
                    }
                }
                // clear
                x.clear();
                lst = beg = b[i].first + 1;
            } else if (lst == b[i].first) {
                x.push_back(b[i].second);
                lst += 1;
            } else {
                lst = -1;
            }
        }

        // cerr << ans << endl;
        if (ans & 1) {
            cout << "Pico" << '\n';
        } else {
            cout << "FuuFuu" << '\n';
        }
    }

    return 0;
}