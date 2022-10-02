#include <bits/stdc++.h>

using namespace std;

map<vector<int>, int> sg[2];

int dfs(vector<int> v, int type) {
    sort(v.begin(), v.end());
    int sum = 0;
    for (int i = 0; i < v.size(); ++i) {
        sum += v[i];
    }
    if (sum <= 0) return sg[type][v] = 0;
    if (sg[type].count(v)) return sg[type][v];
    multiset<int> st;
    if (type == 0) {
        for (int i = 0; i < v.size(); ++i) {
            for (int k = 1; k <= v[i]; ++k) {
                v[i] -= k;
                st.insert(dfs(v, type ^ 1));
                v[i] += k;
            }
        }
    } else {
        for (int i = 0; i < v.size(); ++i) {
            for (int k = 2; k <= v[i]; ++k) {
                v[i] -= k;
                st.insert(dfs(v, type ^ 1));
                v[i] += k;
            }
        }
        for (int i = 0; i < v.size(); ++i) {
            for (int j = i + 1; j < v.size(); ++j) {
                for (int k = 1; k <= v[i]; ++k) {
                    for (int t = 1; t <= v[j]; ++t) {
                        v[i] -= k, v[j] -= t;
                        st.insert(dfs(v, type ^ 1));
                        v[i] += k, v[j] += t;
                    }
                }
            }
        }
    }
    int cnt = 0;
    for (auto u : st) {
        if (u > cnt) {
            break;
        }
        ++cnt;
    }

    return sg[type][v] = cnt;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int ans;
    if (n > 5) {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            if (1 != a) cnt += 1;
        }
        if (1 == cnt) {
            ans = 1;
        } else if (0 == cnt) {
            if (0 == n % 3)
                ans = 0;
            else
                ans = 1;
        } else {
            ans = 0;
        }
    } else {
        vector<int> v;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            v.emplace_back(a);
        }
        ans = dfs(v, 0);
    }

    if (ans) {
        cout << "Win" << endl;
    } else {
        cout << "Lose" << endl;
    }

    return 0;
}