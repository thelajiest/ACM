#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define int ll
using T = long double;
const T PI = std::acos(-1);

vector<T> f;
vector<T> R, I;
int n, k;

T max_F(int x) {
    T ans = 0;
    for (int t = 0; t < n; ++t) {
        T alpha = -2.0 * PI * k * t / n;
        T nR = R[t] - 1.0 * (f[k] - x) * cos(alpha);
        T nI = I[t] - 1.0 * (f[k] - x) * sin(alpha);
        ans = max(ans, nR * nR + nI * nI);
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        f.push_back(a);
    }

    R.resize(n);
    I.resize(n);
    for (int t = 0; t < n; ++t) {
        for (int s = 0; s < n; ++s) {
            T alpha = -2.0 * PI * s * t / n;
            R[t] += 1.0 * f[s] * cos(alpha);
            I[t] += 1.0 * f[s] * sin(alpha);
        }
    }

    int l = -1E9, r = 1E9;
    int H = 1;
    while (r - l > H) {
        // cout << l << " " << r << endl;
        int l1 = (l * 2 + r) / 3, r1 = (r * 2 + l) / 3;
        T f1 = max_F(l1);
        T f2 = max_F(r1);
        if (f1 <= f2) {
            r = r1 - 1;
        } else {
            l = l1 + 1;
        }
    }

    // cout << max_F(1) << endl;

    T ans = min(max_F(l), max_F(r));

    std::cout << std::fixed << std::setprecision(10) << sqrt((double)ans)
              << std::endl;

    return 0;
}