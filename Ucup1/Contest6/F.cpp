#include <bits/stdc++.h>
using i64 = std::int64_t;
constexpr int INF = 1E9;

void solve() {
    int n;
    std::cin >> n;
    std::vector par(n, -1);

    std::vector<int> a;
    for (int i = 0; i < 2 * n - 1; i++) {
        int x;
        std::cin >> x;
        x--;
        a.push_back(x);
    }

    int l = -1, r = -1;
    for (int i = 0, j; i < 2 * n - 1; i = j) {
        j = i;
        if (a[i] != -1) {
            j++;
            continue;
        }
        while (a[j] == -1) j++;

        l = i, r = j - 1;
    }

    std::vector<int> cntl(n), cntr(n);
    for (int i = 0; i < l; i++) {
        cntl[a[i]]++;
    }
    for (int i = r + 1; i < 2 * n - 1; i++) {
        cntr[a[i]]++;
    }

    std::vector<int> ans;

    std::set<int> unvis;
    for (int i = 0; i < n; i++) unvis.insert(i);

    std::vector<int> vis(n);
    int cnt = 0;

    if (a[0] != -1) {
        ans.push_back(a[0]);
        unvis.erase(unvis.find(a[0]));
        vis[a[0]] = 1;
    } else {
        ans.push_back(0);
        unvis.erase(unvis.find(0));
        vis[0] = 1;
    }

    for (int i = 1; i < 2 * n - 1; i++) {
        if (a[i] != -1) {
            ans.push_back(a[i]);
            if (!vis[a[i]]) {
                vis[a[i]] = 1;
                par[a[i]] = ans[i - 1];
                unvis.erase(unvis.find(a[i]));
            }
        } else {
            int next = (unvis.size() == 0) ? INF : (*unvis.begin());
            int last = (par[ans.back()] == -1) ? INF : par[ans.back()];
            if (cntr[ans.back()] > 0) last = INF;

            if (next == INF && last == INF) {
                std::cout << "fool" << std::endl;
                exit(0);
            }
            if (next < last) {
                unvis.erase(unvis.begin());
                vis[next] = 1;
                par[next] = ans.back();
                ans.push_back(next);
            } else {
                ans.push_back(last);
            }
        }
    }

    for (int i = 0; i < 2 * n - 1; i++) {
        std::cout << ans[i] + 1 << " \n"[i == 2 * n - 2];
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}