#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;

vector<int> prime_enumerate(int N) {
    vector<bool> sieve(N / 3 + 1, 1);
    for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn;
         p += d = 6 - d, i++) {
        if (!sieve[i]) continue;
        for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                 qe = sieve.size();
             q < qe; q += r = s - r)
            sieve[q] = 0;
    }
    vector<int> ret{2, 3};
    for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
        if (sieve[i]) ret.push_back(p);
    while (!ret.empty() && ret.back() > N) ret.pop_back();
    return ret;
}

constexpr int N = 2000;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    vector<int> a(n + 1);
    vector<int> b(m + 1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];

    auto primes = prime_enumerate(N);

    for (auto p : primes) {
        vector<VI> ma(p), mb(p);

        for (int i = 1; i <= n; i++) ma[a[i] % p].emplace_back(i);
        for (int i = 1; i <= m; i++) mb[b[i] % p].emplace_back(i);
    }
}