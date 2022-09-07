#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
const long double pi = acos(-1);
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int _;
    cin >> _;
    long double m4 = asin(cos(pi / 3) / sin(pi / 3));
    long double m6 = asin(cos(pi / 3) / sin(pi / 4));
    long double m8 = asin(cos(pi / 4) / sin(pi / 3));
    long double m12 = asin(cos(pi / 3) / sin(pi / 5));
    long double m20 = asin(cos(pi / 5) / sin(pi / 3));
    while (_--) {
        int n;
        long double a;
        int k;
        cin >> n >> a >> k;
        if ((n != 4) && (n != 6) && (n != 8) && (n != 12) && (n != 20))
            cout << "impossible" << '\n';
        else {
            cout << "possible ";
            cout << fixed << setprecision(12);
            if (n == 4) {
                for (int i = 1; i <= k; i++) {
                    a = a * (tan(30 * pi / 180) * sin(m4));
                }
                cout << n << " " << a << '\n';
            }
            if (n == 6 || n == 8) {
                for (int i = 1; i <= k; i++) {
                    if (n == 6) {
                        a = a * (tan(pi / 4) * sin(m6));
                        n = 8;
                    } else {
                        a = a * (tan(pi / 6) * sin(m8));
                        n = 6;
                    }
                }
                cout << n << " " << a << '\n';
            }

            if (n == 12 || n == 20) {
                for (int i = 1; i <= k; i++) {
                    if (n == 12) {
                        a = a * (tan(54 * pi / 180) * sin(m12));
                        n = 20;

                    } else if (n == 20) {
                        a = a * (tan(pi / 6) * sin(m20));
                        n = 12;
                    }
                }

                cout << n << " " << a << '\n';
            }
        }
    }
}