#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    vector<int> cnt(26);
    for (auto p : s) cnt[p - 'a']++;
    for (int i = 0; i <= 25; i++)
        if (cnt[i] >= 17) {
            for (int j = 0; j <= 16; j++) cout << char(i + 'a');
            return 0;
        }
    fill(cnt.begin(), cnt.end(), 0);

    vector<int> vis(n);
    vector<char> ans;
    int t = 0;
    vector<int> g = {5, 7, 5};
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        cnt[s[i] - 'a']++;

        for (int j = 0; j <= 25; j++)
            if (cnt[j] == g[t]) {
                for (int k = 0; k <= i; k++) {
                    if (s[k] == char(j + 'a')) vis[k] = 1;
                }
                for (int k = 0; k < g[t]; k++) ans.push_back(char(j + 'a'));
                t++;
                fill(cnt.begin(), cnt.end(), 0);
            }
        if (ans.size() == 17) break;
    }

    if (ans.size() == 17) {
        for_each(begin(ans), end(ans), [&](char s) { cout << s; });
    } else
        cout << "none";
}