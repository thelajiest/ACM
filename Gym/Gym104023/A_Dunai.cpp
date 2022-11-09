#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[5], b[5];
bool tpb[5], tpc[5];
set<string> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 5; ++j) {
            string tmp;
            cin >> tmp;
            st.insert(tmp);
        }
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string tmp;
        int p;
        cin >> tmp >> p;
        if (st.end() != st.find(tmp)) {
            a[p - 1] += 1;
        } else {
            b[p - 1] += 1;
        }
    }

    int ans1 = 10000, ans2 = 10000;
    for (int i = 0; i < 5; ++i) {
        ans1 = min(ans1, a[i]);
        ans2 = min(ans2, b[i]);
    }

    // for (int i = 0; i < 5; ++i) {
    //     cerr << a[i] << ' ' << b[i] << endl;
    // }
    // cerr << endl;
    // cerr << ans1 << ' ' << ans2 << endl;

    for (int i = 0; i < 5; ++i) {
        a[i] -= ans1;
        b[i] -= ans2;
    }

    // 冠军队不够拆
    if (4 * ans1 < ans2) {
        ans2 -= 4 * ans1;
        ans1 = 5 * ans1;
    } else {
        ans1 = ans1 + ans2;
        ans2 = 0;
    }

    // for (int i = 0; i < 5; ++i) {
    //     cerr << a[i] << ' ' << b[i] << endl;
    // }
    // cerr << endl;
    // cerr << ans1 << ' ' << ans2 << endl;

    while (ans2 > 0) {
        int mx = 0, mxi = -1;
        for (int i = 0; i < 5; ++i) {
            if (a[i] > 0 && a[i] + b[i] > mx) {
                mx = a[i] + b[i];
                mxi = i;
            }
        }
        if (-1 == mxi) break;
        a[mxi] -= 1;
        ans2 -= 1;
        ans1 += 1;
    }

    ans2 = 10000;
    for (int i = 0; i < 5; ++i) {
        ans2 = min(ans2, a[i] + b[i]);
    }
    cout << ans1 + ans2 << endl;

    return 0;
}