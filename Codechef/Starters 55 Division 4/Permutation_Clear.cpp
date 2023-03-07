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
        int n = 1;
        cin >> n;
        vector<int> a(n);
        for (auto&& it : a) cin >> it;
        int k;
        cin >> k;
        set<int> se;
        for (int i = 1; i <= k; i++) {
            int x;
            cin >> x;
            se.insert(x);
        }
        for (auto p : a) {
            if (se.find(p) == se.end()) cout << p << " ";
        }

        cout << '\n';
    }

    return 0;
}
