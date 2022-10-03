#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n == 3) {
        cout << "5 9 1\n3 7 8\n6 2 4\n";
        return 0;
    }
    if (n == 4) {
        cout << "15 11 16 12\n13 3 6 9\n14 7 8 1\n4 2 10 5\n";
        return 0;
    }
    if (n == 5) {
        cout << "1 5 7 11 13\n17 19 23 3 9\n15 21 25 24 12\n18 6 2 22 4\n8 10 "
                "14 16 20\n";
        return 0;
    }
    vector<vector<int>> ans(n + 1, vector<int>(n + 1));

    if (n % 2 == 0) {
        vector<int> odd, even;
        vector<int> odd3, even3;
        for (int i = 1; i <= n * n; i++) {
            if (i & 1) {
                if (i % 3 == 0 && odd3.size() < n)
                    odd3.emplace_back(i);
                else
                    odd.emplace_back(i);
            } else {
                if (i % 3 == 0 && even3.size() < n)
                    even3.emplace_back(i);
                else
                    even.emplace_back(i);
            }
        }
        int now = 0;
        for (int i = 1; i <= n / 2 - 1; i++) {
            for (int j = 1; j <= n; j++) {
                ans[i][j] = even[now++];
            }
        }
        now = 0;
        for (int i = 1; i <= n; i++) ans[n / 2][i] = even3[now++];
        now = 0;
        for (int i = 1; i <= n; i++) ans[n / 2 + 1][i] = odd3[now++];
        now = 0;
        for (int i = n / 2 + 2; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                ans[i][j] = odd[now++];
            }
        }
    } else {
        vector<int> odd, even;
        vector<int> odd3, even3;
        for (int i = 1; i <= n * n; i++) {
            if (i & 1) {
                if (i % 3 == 0 && odd3.size() < n)
                    odd3.emplace_back(i);
                else
                    odd.emplace_back(i);
            } else {
                if (i % 3 == 0 && even3.size() < n)
                    even3.emplace_back(i);
                else
                    even.emplace_back(i);
            }
        }
        int now = 0;
        for (int i = 1; i <= n / 2 - 1; i++) {
            for (int j = 1; j <= n; j++) ans[i][j] = odd[now++];
        }
        for (int i = 1; i <= n / 2 + 1; i++) ans[n / 2][i] = odd[now++];
        now = 0;
        for (int i = n / 2 + 2; i <= n; i++) ans[n / 2][i] = odd3[now++];
        for (int i = 1; i <= n / 2 + 1; i++) ans[n / 2 + 1][i] = odd3[now++];
        now = 0;
        for (int i = n / 2 + 2; i <= n; i++) ans[n / 2 + 1][i] = even3[now++];
        for (int i = 1; i <= n / 2 + 1; i++) ans[n / 2 + 2][i] = even3[now++];
        now = 0;
        for (int i = n / 2 + 2; i <= n; i++) ans[n / 2 + 2][i] = even[now++];
        for (int i = n / 2 + 3; i <= n; i++) {
            for (int j = 1; j <= n; j++) ans[i][j] = even[now++];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}