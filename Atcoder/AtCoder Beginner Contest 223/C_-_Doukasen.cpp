#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr double EPS = 1E-8;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> a(n);

    for (auto& [x, y] : a) cin >> x >> y;

    double L = 0.0;
    for (auto [x, y] : a) L += x;

    double l = 0, r = 1E9;

    while (fabs(r - l) > EPS) {
        double mid = (r + l) / 2.0;

        auto check = [&](double t) -> bool {
            double lb = 0.0;
            double tnow = t;
            for (int i = 0; i < n; i++) {
                auto [l, s] = a[i];
                if (fabs(tnow) < EPS) break;
                if (1.0 * l / (1.0 * s) > tnow) {
                    lb += tnow * s;
                    break;
                } else {
                    tnow -= 1.0 * l / (1.0 * s);
                    lb += l;
                }
            }

            double rb = 0.0;

            tnow = t;
            for (int i = n - 1; i >= 0; i--) {
                auto [l, s] = a[i];
                if (fabs(tnow) < EPS) break;
                if (1.0 * l / (1.0 * s) > tnow) {
                    rb += tnow * s;
                    break;
                } else {
                    tnow -= 1.0 * l / (1.0 * s);
                    rb += l;
                }
            }
            return (lb + rb >= L);
        };
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    double ansl = l;
    double lb = 0.0;
    double tnow = ansl;
    for (int i = 0; i < n; i++) {
        auto [l, s] = a[i];
        if (1.0 * l / (1.0 * s) > tnow) {
            lb += tnow * s;
            break;
        } else {
            tnow -= 1.0 * l / (1.0 * s);
            lb += l;
        }
    }

    cout << fixed << setprecision(15);
    cout << lb << '\n';

    return 0;
}