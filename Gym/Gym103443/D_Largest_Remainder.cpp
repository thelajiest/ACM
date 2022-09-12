#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAX_S = 1 << 16 | 1;
const int MAX_K = 210;
const int MAX_D = 17;
int f[MAX_S][MAX_K];
int dig[MAX_D], kmod[MAX_D], ans[MAX_K];
pii pre[MAX_S][MAX_K];
int d, k;
queue<pii> q;

void print(int s, int mod) {
    int pos = d - 1;
    while (f[s][mod] != -1) {
        ans[f[s][mod]] = dig[pos];
        pii p = pre[s][mod];
        s = p.first;
        mod = p.second;
        --pos;
    }
    for (int pos = d - 1; pos >= 0; --pos) cout << ans[pos];
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> d >> k;
    for (int i = 0; i < d; ++i) cin >> dig[i];

    sort(dig, dig + d, less<int>());
    int S = (1 << d);
    for (int prod = 1 % k, i = 0; i < d; ++i) {
        kmod[i] = prod;
        prod = prod * 10 % k;
    }

    auto brute_force = [&]() -> vector<int> {
        vector<int> res;
        vector<vector<int>> ans(k);
        for (int i = 0; i < d; i++) res.push_back(dig[i]);
        sort(begin(res), end(res));
        do {
            int now = 0;
            for (int i = 0; i < d; i++) {
                now = (now + kmod[i] * res[i]) % k;
            }
            auto comp = [](vector<int> a, vector<int> b) -> bool {
                if (a.size() == 0)
                    return true;
                else {
                    for (int i = int(a.size()) - 1; i >= 0; i--)
                        if (a[i] > b[i]) return false;
                }
                return true;
            };
            if (comp(ans[now], res)) ans[now] = res;
        } while (next_permutation(begin(res), end(res)));
        for (int i = k - 1; i >= 0; i--) {
            if (ans[i].size() != 0) {
                reverse(begin(ans[i]), end(ans[i]));
                return ans[i];
            }
        }
        return vector<int>();
    };
    // auto bf = brute_force();
    // for (auto p : bf) cerr << p;
    for (int s = 0; s < S; ++s)
        for (int mod = 0; mod < k; ++mod) f[s][mod] = -1;
    pre[0][0] = make_pair(-1, 0);
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        pii p = q.front();
        q.pop();
        int s = p.first, mod = p.second;
        int i = __builtin_popcount(s);
        if (i >= d) continue;
        for (int j = d - 1; j >= 0; --j) {
            if ((s >> j) & 1) continue;
            int _s = s | (1 << j), _mod = (mod + kmod[j] * dig[i]) % k;
            pre[_s][_mod] = make_pair(s, mod);
            if (f[_s][_mod] == -1) q.push(make_pair(_s, _mod));
            f[_s][_mod] = j;
        }
    }
    for (int mod = k - 1; mod >= 0; --mod) {
        if (~f[S - 1][mod]) {
            // cout << mod << "\n";
            print(S - 1, mod);
            break;
        }
    }
    return 0;
}