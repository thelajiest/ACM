#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int _;
    cin >> _;
    while (_--) {
        int a, b, c;
        cin >> a >> b >> c;

        i64 ans = 1;
        for (int i = 0; i <= 20; i++) {
            int nowa = (a >> i) & 1;
            int nowb = (b >> i) & 1;
            int nowc = (c >> i) & 1;
            int res = 0;
            for (int t1 = 0; t1 <= 1; t1++)
                for (int t2 = 0; t2 <= 1; t2++)
                    for (int t3 = 0; t3 <= 1; t3++)
                        if (((t1 | t2) == nowa) && ((t1 | t3) == nowb) &&
                            ((t3 | t2) == nowc))
                            res++;
            ans *= res;
        }
        cout << ans << '\n';
    }
}