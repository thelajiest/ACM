#include <bits/stdc++.h>
using namespace std;

string a, b;
string cur;

int cnt[10];
bool is_fx[10], is_mi[10];

vector<string> ans;

void get_cnt() {
    for (int i = 0; i < 8; ++i) {
        if (2 == i || 5 == i) continue;
        if ('G' == b[i] || 'P' == b[i]) cnt[a[i] - '0'] += 1;
        if ('B' == b[i]) is_fx[a[i] - '0'] = true;
        if ('P' == b[i]) is_mi[a[i] - '0'] = true;
    }
}

bool check() {
    for (int i = 0; i < 10; ++i) {
        if (0 != cnt[i] && is_fx[i]) return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (cnt[i] > 0 && is_mi[i]) return false;
    }

    for (int i = 0; i < 8; ++i) {
        if (2 == i || 5 == i) continue;
        if ('G' == b[i] && a[i] != cur[i]) return false;
        if (('B' == b[i] || 'P' == b[i]) && a[i] == cur[i]) return false;
    }

    return true;
}

void dfs(int u, int num, bool flag1, bool flag2) {
    if (8 == u) {
        if (check() && 0 == num) {
            ans.push_back(cur);
        }
        return;
    }
    if (2 == u) {
        cur.push_back('+');
        dfs(u + 1, num, false, false);
        cur.pop_back();
    } else if (5 == u) {
        cur.push_back('=');
        dfs(u + 1, num, false, true);
        cur.pop_back();
    } else {
        int fac = flag2 ? -1 : 1;
        for (int i = 0; i < 10; ++i) {
            if (flag1) {
                num += i * fac;
            } else {
                num += 10 * i * fac;
            }
            cur.push_back(i + '0');
            cnt[i] -= 1;
            dfs(u + 1, num, true, flag2);
            cnt[i] += 1;
            cur.pop_back();
            if (flag1) {
                num -= i * fac;
            } else {
                num -= 10 * i * fac;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> a >> b;
    get_cnt();
    dfs(0, 0, false, false);
    cout << ans.size() << '\n';
    for (auto it : ans) {
        cout << it << '\n';
    }

    return 0;
}
