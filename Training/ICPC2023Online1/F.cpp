#include <bits/stdc++.h>

using namespace std;

struct Timer {
    std::chrono::high_resolution_clock::time_point st;

    Timer() { reset(); }

    void reset() { st = std::chrono::high_resolution_clock::now(); }

    std::chrono::milliseconds::rep elapsed() {
        auto ed = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(ed - st)
            .count();
    }
};

typedef pair<int, int> pii;
const int MAX_N = 5e5 + 7;
const long long INF = 1e18;

struct Node {
    int l, r;
    int dep, siz;
};

int T, n, tot;
int L;
long long a[MAX_N];
int num[MAX_N * 70];
map<long long, int> mp;
Node trie[MAX_N * 70];

void insert(long long x, int y) {
    int u = 1;
    for (int i = 0; i < L; i++) {
        int nxt_u;
        trie[u].siz += y;
        if ((x >> i) & 1) {
            nxt_u = trie[u].l;
            if (!nxt_u) {
                nxt_u = ++tot;
            }
            trie[u].l = nxt_u;
            trie[nxt_u].dep = trie[u].dep + 1;
        } else {
            nxt_u = trie[u].r;
            if (!nxt_u) {
                nxt_u = ++tot;
            }
            trie[u].r = nxt_u;
            trie[nxt_u].dep = trie[u].dep + 1;
        }
        u = nxt_u;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Timer sl;
    sl.reset();
    cin >> T;
    while (T--) {
        cin >> n;
        L = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            long long x = a[i];
            int l = 0;
            while (x) {
                x >>= 1;
                ++l;
            }
            L = max(L, l + 1);
        }
        for (int i = 1; i <= n; ++i) {
            ++mp[a[i]];
        }
        vector<int> cnt;
        vector<pair<long long, int>> vec;
        ++tot;
        for (auto p : mp) {
            cnt.push_back(p.second);
            vec.push_back(make_pair(p.first, p.second));
        }
        for (auto p : vec) {
            insert(p.first, p.second);
        }
        long long ans = 1ll * n * (n - 1) / 2 * (n - 2) / 3;
        for (int i = 0; i < (int)cnt.size(); ++i) {
            ans -= 1ll * cnt[i] * (cnt[i] - 1) / 2 * (cnt[i] - 2) / 3;
        }
        for (auto p : vec) {
            long long x = p.first;
            int y = p.second;
            int u = 1;

            for (int i = 0; i < L; i++) {
                int nxt = ((x >> i) & 1) ? trie[u].l : trie[u].r;
                int anxt = ((x >> i) & 1) ? trie[u].r : trie[u].l;
                if (!(trie[u].dep & 1)) {
                    if (nxt) {
                        ans -= 1ll * y * (y - 1) / 2 * trie[anxt].siz;
                    }
                }
                u = nxt;
            }
        }
        mp.clear();
        for (int i = 1; i <= tot; ++i) {
            trie[i].l = trie[i].r = trie[i].dep = trie[i].siz = 0;
            num[i] = 0;
        }
        tot = 0;
        cout << ans << "\n";
    }
    cout << sl.elapsed() << "\n";
    return 0;
}