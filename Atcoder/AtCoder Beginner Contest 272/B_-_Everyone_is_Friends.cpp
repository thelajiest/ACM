#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> pt(n + 1);

    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        for (int j = 1; j <= x; j++) {
            int now;
            cin >> now;
            pt[now].push_back(i);
        }
    }
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            vector<int> res(m + 1);
            for (auto it : pt[i]) res[it]++;
            for (auto it : pt[j]) res[it]++;
            bool ok = false;
            for (int g = 1; g <= m; g++)
                if (res[g] >= 2) ok = true;
            if (!ok) ans = 0;
        }
    }

    if (ans)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}