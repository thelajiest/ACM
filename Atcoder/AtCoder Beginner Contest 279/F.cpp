#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 7;
int fa[MAX_N << 1], val[MAX_N << 1];
int bottle[MAX_N];
int n, q;

int get_fa(int x) {
    if (x == fa[x]) return fa[x];
    int t = fa[x];
    fa[x] = get_fa(fa[x]);
    val[x] = val[t];
    return fa[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) fa[i] = i, val[i] = i, bottle[i] = i;
    int k = n;
    while (q--) {
        int op, x, y;
        cin >> op;
        if (op == 1) {
            cin >> x >> y;
            if (bottle[x]) {
                fa[bottle[y]] = bottle[x];
            } else {
                bottle[x] = bottle[y];
            }
            val[bottle[y]] = x;
            bottle[y] = 0;
        } else if (op == 2) {
            cin >> x;
            ++k;
            if (bottle[x]) {
                fa[k] = bottle[x];
            } else {
                fa[k] = k;
                bottle[x] = k;
            }
            val[k] = x;
        } else {
            cin >> x;
            get_fa(x);
            cout << val[x] << "\n";
        }
    }
    return 0;
}