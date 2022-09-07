#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<i64> a(n);
    vector<vector<i64>> mp(16, vector<i64>(n));
    srand(time(0));
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j <= 15; j++)
            if ((a[i] >> j) & 1) mp[j][i]++;
    }
    for (int i = 0; i < 16; i++) sort(mp[i].begin(), mp[i].end());
    vector<i64> b(n);
    for (int i = 0; i < n; i++) {
        i64 res = 0;
        for (int j = 0; j <= 15; j++) res += (mp[j][i] << j);
        b[i] = res;
    }
    using frac = pair<i64, i64>;
    i64 ave = 0, tot = 0;
    for (int i = 0; i < n; i++) {
        ave += b[i];
        tot += b[i] * b[i];
    }
    ave = ave * ave;
    i64 sum = 0;
    sum = (n * tot - ave);

    i64 m = gcd(sum, n);
    cout << sum / m << "/" << n / m;

    // for (int t = 0; t <= 100000; t++) {
    //     int i = rand() % n;
    //     int j = rand() % n;
    //     if (i == j) continue;
    //     int aa = a[i] | a[j];
    //     int bb = a[i] & a[j];
    //     a[i] = aa;
    //     a[j] = bb;
    // }
    // for (int i = 0; i < n; i++) cerr << a[i] << " \n"[i == n - 1];
    // 100
    // 110
    // 011
    // 010
    // 001
}