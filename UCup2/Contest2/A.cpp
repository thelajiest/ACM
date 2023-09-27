#include <bits/stdc++.h>

using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<int> prefix(n + 1, n);
    std::vector<std::pair<int, int>> suffix(n + 1, {n, n});

    std::map<char, int> mp;
    mp['s'] = n;
    mp['p'] = n;
    mp['b'] = n;
    mp['u'] = n;

    for (int i = 0; i < n; i++) {
        mp[s[i]] = i;
        if (s[i] == 's') {
            prefix[i] = mp['b'];
        }
        if (s[i] == 'p') {
            prefix[i] = mp['s'];
        }
        if (s[i] == 'b') {
            prefix[i] = mp['p'];
        }
        if (s[i] == 'u') {
            prefix[i] = mp['s'];
        }
    }

    mp.clear();
    mp['s'] = n;
    mp['p'] = n;
    mp['b'] = n;
    mp['u'] = n;

    for (int i = n - 1; i >= 0; i--) {
        mp[s[i]] = i;
        if (s[i] == 's') {
            suffix[i].first = mp['p'];
            suffix[i].second = mp['u'];
        }
        if (s[i] == 'p') {
            suffix[i].first = mp['b'];
        }
        if (s[i] == 'b') {
            suffix[i].first = mp['s'];
        }
    }

    prefix[n] = n;
    suffix[n] = {n, n};
    i64 ans = 1E18;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') {
            i64 curans = 0;
            int r = i;
            int l = prefix[r];
            curans += i - l - 1;
            r = l;
            l = prefix[r];
            curans += i - l - 2;

            // std::cerr << l << std::endl;
            if (l == n) continue;

            l = i;
            r = suffix[l].first;
            curans += r - i - 1;
            l = r;
            r = suffix[l].second;
            curans += r - i - 2;
            // std::cerr << r << std::endl;

            if (r == n) continue;
            // std::cerr << l << " " << r << std::endl;

            ans = std::min(ans, curans);
            // std::cerr << ans << std::endl;
            // std::cerr << std::endl;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}