#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
struct point {
    double x, y, z;
};
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<point> t(n);
    for (int i = 0; i < n; i++) {
        auto& [x, y, z] = t[i];
        cin >> x >> y >> z;
    }
    vector<point> res;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            point now;
            now.x = t[i].x + t[j].x;
            now.y = t[i].y + t[i].y;
            now.z = t[i].z + t[i].z;
            res.push_back(now);
        }
    }
    cout << res.size() << '\n';
    for (auto [x, y, z] : res) {
        cout << fixed << setprecision(10);
        cout << x << " " << y << " " << z << endl;
    }
    return 0;
}