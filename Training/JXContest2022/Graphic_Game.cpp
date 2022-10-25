#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 2E6 + 1;

array<int, N> cnt, del, head;
array<set<int>, N> mp;
struct Edge {
    int next;
    int to;
};
int ps = 0;
array<Edge, N> edge;

void add(int u, int v) {
    edge[ps].to = v;
    edge[ps].next = head[u];
    head[u] = ps++;
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    head.fill(-1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        cnt[u]++, cnt[v]++;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= 2 * n; i++) {
        mp[cnt[i]].insert(i);
    }
    int p = 2 * n;
    while (p >= 0) {
        if (mp[p].size() >= 2) {
            int x = *mp[p].begin();
            mp[p].erase(x);
            int y = *mp[p].begin();
            mp[p].erase(y);
            del[x] = 1, del[y] = 1;

            cout << x << " " << y << '\n';
            for (int i = head[x]; ~i; i = edge[i].next) {
                int v = edge[i].to;
                if (del[v]) continue;
                mp[cnt[v]].erase(mp[cnt[v]].find(v));
                cnt[v]--;
                mp[cnt[v]].insert(v);
            }
            for (int i = head[y]; ~i; i = edge[i].next) {
                int v = edge[i].to;
                if (del[v]) continue;
                mp[cnt[v]].erase(mp[cnt[v]].find(v));
                cnt[v]--;
                mp[cnt[v]].insert(v);
            }
            continue;
        }
        p--;
    }
    return 0;
}