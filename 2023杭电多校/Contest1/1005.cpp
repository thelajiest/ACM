#include <bits/stdc++.h>

using i64 = std::int64_t;

std::string minCyclicString(std::string s) {
    s += s;
    int n = s.size();
    int i = 0, ans = 0;
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) i += j - k;
    }
    return s.substr(ans, n / 2);
}

void solve() {
    std::map<std::string, int> hash;

    int n, m;
    std::cin >> n >> m;
    std::vector<int> id(n + 1);

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        s = minCyclicString(s);
        if (hash.count(s)) {
            id[i] = hash[s];
        } else {
            hash[s] = ++cnt;
            id[i] = hash[s];
        }
    }

    int q;
    std::cin >> q;

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        if (id[x] == id[y])
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
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