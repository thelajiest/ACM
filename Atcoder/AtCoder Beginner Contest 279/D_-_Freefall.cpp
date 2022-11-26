#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double A, B;

    cin >> A >> B;

    i64 l = 0, r = 1E18;

    auto solve = [&](double x) -> double { return B * x + A / sqrt(1 + x); };
    while ((r - l) >= 100) {
        i64 m1 = (l + l + r) / 3;
        i64 m2 = (r + l + r) / 3;
        double tp1 = solve(m1);
        double tp2 = solve(m2);
        if (tp1 > tp2)
            l = m1;
        else
            r = m2;
    }

    double ans = solve(l);
    for (int i = l; i <= r; i++) {
        ans = min(ans, solve(i));
    }
    cout << fixed << setprecision(10);
    cout << ans;
    return 0;
}