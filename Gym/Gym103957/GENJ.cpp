#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("J.in", "w", stdout);

    cout << 100 << '\n';
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> dis(1, 100000);
    for (int i = 1; i <= 100; i++) {
        cout << 100000 << '\n';
        for (int j = 1; j <= 100000; j++) {
            double a = dis(gen);
            double b = dis(gen);
            cout << fixed << setprecision(4) << a << " " << b << '\n';
        }
    }
    return 0;
}