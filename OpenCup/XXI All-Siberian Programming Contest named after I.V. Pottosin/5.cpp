#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
#define int i64
unordered_map<int, int> bit;
constexpr int Blocks = 25000;
signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto ask = [&](int x) -> int {
        cout << "read " << x << endl;
        cout.flush();
        int ans;
        cin >> ans;
        bit[x] = ans;
        return ans;
    };
    int n;
    cin >> n;
    int now = 0;
    vector<int> prefix{-1}, suffix{n};
    bool flag1 = false, flag2 = false;
    for (int i = 0; i < Blocks; i++) {
        bit[now] = ask(now);
        int tmp = bit[now];
        now = now + tmp + 1;
        if (now >= n) break;
        int check = ask(now);
        if (now == n - 1 && check == tmp) flag1 = true;
        if (check != tmp) break;
        prefix.push_back(now);
        now++;
        if (now >= n) break;
    }
    now = n - 1;
    for (int i = 0; i < Blocks; i++) {
        bit[now] = ask(now);
        int tmp = bit[now];
        now = now - tmp - 1;
        if (now < 0) break;
        int check = ask(now);
        if (now == 0 && check == tmp) flag2 = true;

        if (check != tmp) break;
        suffix.push_back(now);
        now--;
        if (now < 0) break;
    }
    if (flag1 && flag2) {
        cout << "fix 0" << endl;
        cout.flush();
        return 0;
    }
    if (prefix.size() > 0) {
        int ep = bit[prefix.back() + 1] + prefix.back() + 1 + 1;
        for (auto it : suffix) {
            if (it - 1 == ep) {
                cout << "fix 1" << endl;
                cout.flush();
                cout << it - 1 << " " << bit[prefix.back() + 1];
                cout.flush();
                return 0;
            }
        }
    } else {
        int ep = bit[0] + 1;
        for (auto it : suffix) {
            if (it - 1 == ep) {
                cout << "fix 1" << endl;
                cout.flush();
                cout << it - 1 << " " << bit[0];
                cout.flush();
                return 0;
            }
        }
    }
    if (suffix.size() > 0) {
        int es = -bit[suffix.back() - 1] + suffix.back() - 1 - 1;
        for (auto it : prefix) {
            if (it + 1 == es) {
                cout << "fix 1" << endl;
                cout.flush();
                cout << it + 1 << " " << bit[suffix.back() - 1];
                cout.flush();
                return 0;
            }
        }
    } else {
        int es = n - bit[n - 1] - 2;
        for (auto it : prefix) {
            if (it + 1 == es) {
                cout << "fix 1" << endl;
                cout.flush();
                cout << it + 1 << " " << bit[n - 1];
                cout.flush();
                return 0;
            }
        }
    }
    cout << "fix 2" << endl;
    cout.flush();
    cout << 0 << " " << n - 2 << endl;
    cout.flush();
    cout << n - 1 << " " << n - 2 << endl;
    cout.flush();
    return 0;
}