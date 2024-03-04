#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAX_N = 1E6 + 100;

int T;
int n, k;
int a[MAX_N];
int tp[40];  // 记录各位选择情况：1必为0，2必为1，-1为0小，-2为1小
bool fail;

void dfs(int l, int r, int loc, bool first) {
    if (loc < 0) return;

    int msk = 1ll << loc;
    // 区间左右皆闭
    int cur = a[l] & msk, mid = -1;
    for (int i = l; i <= r; ++i) {
        if ((a[i] & msk) != cur) {
            if (mid == -1) {
                mid = i - 1;
            }
        } else if (mid != -1) {
            fail = true;
            return;
        }
    }

    // 可自由选择
    if (-1 == mid) {
        if (first) {
            tp[loc] = cur ? -2 : -1;  // 若全1，为1小，否则为0小
        }
        dfs(l, r, loc - 1, first);
    } else {
        int tar = cur ? 2 : 1;
        if (tp[loc] <= 0)
            tp[loc] = tar;
        else if (tp[loc] != tar) {
            fail = true;
            return;
        }
        dfs(l, mid, loc - 1, first);
        dfs(mid + 1, r, loc - 1, false);
    }
    // cerr << "tar " << l << ' ' << r << ':' << loc << ',' << tp[loc] << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 0; i < 30; ++i) tp[i] = 0;
        fail = false;

        a[1] = 0;
        for (int i = 2; i <= n; ++i) {
            cin >> a[i];
            a[i] ^= a[i - 1];
        }

        // 当且仅当某个数位全部相同时可能有两种情况
        // 否则首先必须前后分界
        // 条件递归向下
        // 大小选择由最靠前的一组决定
        dfs(1, n, 29, true);

        // cerr << "err ";
        // for (int i = 4; i >= 0; --i) {
        //     cerr << tp[i] << ' ';
        // }
        // cerr << '\n';

        int ans = 0;
        if (fail) {
            ans = -1;
        } else {
            int cnt = 0;
            for (int i = 0; i < 30; ++i) {
                if (tp[i] < 0) {
                    cnt += 1;
                } else if (tp[i] == 2) {
                    ans |= 1ll << i;
                }
            }
            if (k > (1 << cnt)) {
                ans = -1;
            } else {
                k -= 1;
                for (int i = 0; i < 30; ++i) {
                    if (tp[i] >= 0) continue;
                    if (k & 1) {
                        // 这一位选大的
                        if (tp[i] == -1) {
                            ans |= 1ll << i;
                        }
                    } else {
                        // 选小的
                        if (tp[i] == -2) {
                            ans |= 1ll << i;
                        }
                    }
                    k >>= 1;
                }
            }
        }

        if (-1 == ans) {
            cout << ans << '\n';
        } else {
            for (int i = 1; i <= n; ++i) {
                cout << (ans ^ a[i]) << ' ';
            }
            cout << '\n';
        }
    }

    std::cout << "hello world" << std::endl;

    std::vector<int> a;
    return 0;
}