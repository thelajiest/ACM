#include <bits/stdc++.h>

using i64 = std::int64_t;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) std::cin >> a[i];
    std::sort(a.begin(), a.end());
    if (n == 1) {
        std::cout << abs(a[0] - a[1]) << '\n';
    } else {
        if (n == 2) {
            n *= 2;
            std::vector<int> a1(n, 0);
            std::vector<int> a2(n, 2);
            std::vector<int> a3 = {-1, -1, -1, 2};
            std::vector<i64> ans;
            i64 cnt = 0;
            for (int i = 0; i < n; i++) cnt += abs(a[i] - a1[i]);
            ans.push_back(cnt);
            cnt = 0;
            for (int i = 0; i < n; i++) cnt += abs(a[i] - a2[i]);
            ans.push_back(cnt);
            cnt = 0;
            for (int i = 0; i < n; i++) cnt += abs(a[i] - a3[i]);
            ans.push_back(cnt);
            std::cout << *(std::min_element(begin(ans), end(ans))) << '\n';
        } else {
            if (n % 2 == 0) {
                n *= 2;
                std::vector<int> a1(n, 0);
                std::vector<int> a3(n);
                for (int i = 0; i < n - 1; i++) a3[i] = -1;
                a3[n - 1] = n / 2;
                std::vector<i64> ans;
                i64 cnt = 0;
                for (int i = 0; i < n; i++) cnt += abs(a[i] - a1[i]);
                ans.push_back(cnt);
                cnt = 0;
                for (int i = 0; i < n; i++) cnt += abs(a[i] - a3[i]);
                ans.push_back(cnt);
                std::cout << *(std::min_element(begin(ans), end(ans))) << '\n';
            } else {
                n *= 2;
                std::vector<int> a1(n, 0);
                std::vector<i64> ans;
                i64 cnt = 0;
                for (int i = 0; i < n; i++) cnt += abs(a[i] - a1[i]);
                ans.push_back(cnt);
                std::cout << *(std::min_element(begin(ans), end(ans))) << '\n';
            }
        }
    }
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