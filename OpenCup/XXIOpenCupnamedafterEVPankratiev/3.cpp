#include <bits/stdc++.h>
#define int long long
// #define sleepy

using namespace std;

typedef pair<int, int> pii;
const double EPS = 1e-11;
const int N = 1e4;
bool chk1[4], chk2[4];

bool super_chk(double feedback) {
    if (fabs(feedback + 1) < EPS) return true;
    return false;
}

pii rotate(int x, int y, int i) {
    if (i == 0) {
        return make_pair(x, y);
    }
    if (i == 1) {
        return make_pair(-y, x);
    }
    if (i == 2) {
        return make_pair(-x, -y);
    }
    if (i == 3) {
        return make_pair(y, -x);
    }
}

signed main() {
    double feedback;
    cout << "? 0 0 1 0" << endl;
    cin >> feedback;
    if (super_chk(feedback)) {
        return 0;
    }
    if (fabs(feedback) < EPS) {
        chk1[1] = chk1[2] = true;
    } else {
        chk1[0] = chk1[3] = true;
    }
    cout << "? 0 0 0 1" << endl;
    cin >> feedback;
    if (super_chk(feedback)) {
        return 0;
    }
    if (fabs(feedback) < EPS) {
        chk2[2] = chk2[3] = true;
    } else {
        chk2[0] = chk2[1] = true;
    }
    int zone = 0;
    for (int i = 0; i < 4; ++i) {
        if (chk1[i] && chk2[i]) {
            zone = i;
        }
    }
#ifdef sleepy
    cerr << zone << endl;
#endif
    int x, y;
    double a = 0, b = 0;
    pii p = rotate(1, 0, zone);
    x = p.first, y = p.second;
    cout << "? 0 0 " << x << " " << y << endl;
    cin >> a;
    if (super_chk(a)) {
        return 0;
    }
    p = rotate(0, 1, zone);
    x = p.first, y = p.second;
    cout << "? 0 0 " << x << " " << y << endl;
    cin >> b;
    if (super_chk(b)) {
        return 0;
    }
    a = sqrt(a * a + b * b);
    double sin_phi = fabs(b / a);
#ifdef sleepy
    cerr << sin_phi << endl;
#endif
    if (fabs(sin_phi - 1) < EPS) {
        double r = 1;
        p = rotate(0, 1, zone);
        x = p.first, y = p.second;
        cout << "? " << x << " " << y << " " << x << " " << y << endl;
        cin >> b;
        if (super_chk(b)) {
            return 0;
        }
        double a_b = sqrt(fabs(a / b));
        double R = r / (1 - a_b);
        x = 0;
        if (fabs(floor(R) - r / (1 - a_b)) < EPS) {
            y = floor(R);
        } else {
            y = ceil(R);
        }
        p = rotate(x, y, zone);
        x = p.first, y = p.second;
        cout << "? " << x << " " << y << " " << x << " " << y << endl;
        cin >> feedback;
        // assert(super_chk(feedback));
    } else {
        double tan_phi = sin_phi / sqrt(1 - sin_phi * sin_phi);
        for (x = 1;; ++x) {
            if (fabs(floor(1.0 * x * tan_phi) * 1.0 / x - tan_phi) < EPS) {
                y = floor(1.0 * x * tan_phi);
                break;
            }
            if (fabs(ceil(1.0 * x * tan_phi) * 1.0 / x - tan_phi) < EPS) {
                y = ceil(1.0 * x * tan_phi);
                break;
            }
        }
        double r = sqrt(x * x + y * y);
        p = rotate(x, y, zone);
        x = p.first, y = p.second;
        cout << "? " << x << " " << y << " " << x << " " << y << endl;
        cin >> b;
        if (super_chk(b)) {
            return 0;
        }
        double a_b = sqrt(fabs(a / b));
        double R = r / (1 - a_b);
        x = round(R / r) * x;
        y = round(R / r) * y;
        // for (x = _x; x <= N; ++x) {
        //     if (fabs(floor(1.0 * x * tan_phi) * 1.0 / x - tan_phi) < EPS) {
        //         y = floor(1.0 * x * tan_phi);
        //         if (fabs(sqrt((double)(x * x + y * y)) - R) < EPS) {
        //             break;
        //         }
        //     }
        //     if (fabs(ceil(1.0 * x * tan_phi) * 1.0 / x - tan_phi) < EPS) {
        //         y = ceil(1.0 * x * tan_phi);
        //         if (fabs(sqrt((double)(x * x + y * y)) - R) < EPS) {
        //             break;
        //         }
        //     }
        // }
        // p = rotate(x, y, zone);
        // x = p.first, y = p.second;
        cout << "? " << x << " " << y << " " << x << " " << y << endl;
        cin >> feedback;
        // assert(super_chk(feedback));
    }
    return 0;
}