#include <bits/stdc++.h>
#define int long long

using namespace std;

struct EEE {
    double l, r;
    int idx;
    bool operator<(const EEE &line) { return l.x * r.y < l.y * r.x; }
};

typedef pair<double, double> pdd;
const double EPS = 1e-6;
const int INF = 1e16;
const int MAX_N = 2e4 + 7;
int w[MAX_N], x[MAX_N], v[MAX_N];
int n, a;

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> a;
    for (int i = 0; i < n; ++i) cin >> w[i] >> x[i] >> v[i];
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        vector<EEE> line;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            double _l, _r;
            if (x[i] > x[j]) {
                if (v[j] > v[i]) {
                    _l = max(x[i] - x[j] - a, 0ll) * 1.0 / (v[j] - v[i]);
                    _r = (x[i] - x[j]) * 1.0 / (v[j] - v[i]);
                } else if (v[i] == v[j]) {
                    if (x[i] - x[j] > a) {
                        _r = -1;
                        _l = 0;
                    } else {
                        _l = 0;
                        _r = INF;
                    }
                } else {
                    _l = 0;
                    _r = (a - (x[i] - x[j])) * 1.0 / (v[i] - v[j]);
                }
            } else if (x[i] == x[j]) {
                if (v[j] >= v[i]) {
                    _l = _r = 0;
                } else {
                    _l = 0;
                    _r = 1.0 * a / (v[i] - v[j]);
                }
            } else {
                if (v[j] >= v[i]) {
                    _l = 0;
                    _r = -1;
                } else {
                    _l = 1.0 * (x[j] - x[i]) / (v[i] - v[j]);
                    _r = 1.0 * (x[j] - x[i] + a) / (v[i] - v[j]);
                }
            }
            if (_l <= _r) {
                line.push_back({_l, _r, j});
            }
        }
        std::sort(line.begin(), line.end());
        int value = 0;
        queue<int> q;
        int ans = 0;
        for (int j = 0; j < (int)(line.size()); ++j) {
#ifdef sleepy
            cout << line[j].l << " " << line[j].r << endl;
#endif
            while ((!q.empty())) {
                if ((line[j].l > line[q.front()].r)) {
                    q.pop();
                    value -= w[line[q.front()].idx];
                } else {
                    break;
                }
            }
            value += w[line[j].idx];
            q.push(j);
            ans = max(ans, value);
        }
#ifdef sleepy
        cout << "ok\n";
#endif
        ans += w[i];
        mx = max(mx, ans);
    }
    cout << mx << "\n";
    return 0;
}