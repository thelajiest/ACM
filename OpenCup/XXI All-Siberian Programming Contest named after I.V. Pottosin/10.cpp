#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<double, double>> p(n);
    for (auto& it : p) cin >> it.first;
    for (auto& it : p) cin >> it.second;
    double mx = numeric_limits<double>::max() / 2;

    double ansK, ansB;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            auto [x, y] = p[i];
            auto [xx, yy] = p[j];
            double nowk = 1.0 * (x - xx) / (y - yy);
            double nowb = x - nowk * y;
            double cnt = 0;
            for_each(p.begin(), p.end(), [&](pair<int, int> a) {
                auto [x, y] = a;
                cnt += abs(x - 1.0 * nowk * y - nowb);
            });
            if (cnt < mx) {
                mx = cnt;
                ansK = nowk;
                ansB = nowb;
            }
        }
    }

    cout << fixed << setprecision(12);
    cout << mx << " " << ansK << " " << ansB;

    return 0;
}