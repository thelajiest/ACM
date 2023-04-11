#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;
const int MAXN = 1005;

int n, m, k;
int binom[MAXN][MAXN];

int pow_mod(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = (1LL * res * a) % MOD;
        a = (1LL * a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void precompute_binom() {
    for (int i = 0; i <= n; i++) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % MOD;
        }
    }
}

int main() {
    cin >> n >> m >> k;
    precompute_binom();
    int ans = 0;
    for (int r1 = 1; r1 <= n; r1++) {
        for (int c1 = 1; c1 <= m; c1++) {
            for (int r2 = r1; r2 <= n; r2++) {
                for (int c2 = c1; c2 <= m; c2++) {
                    int count = (r2 - r1 + 1) * (c2 - c1 + 1);
                    int remaining = k - count;
                    if (remaining < 0) continue;
                    int ways =
                        binom[(n - r2 + r1 - 1) * (m - c2 + c1 - 1)][remaining];
                    ways = (1LL * ways * binom[n][r2 - r1 + 1]) % MOD;
                    ways = (1LL * ways * binom[m][c2 - c1 + 1]) % MOD;
                    ans = (ans + ways) % MOD;
                }
            }
        }
    }
    ans = (1LL * ans * pow_mod(binom[n * m][k], MOD - 2)) % MOD;
    cout << ans << endl;
    return 0;
}
