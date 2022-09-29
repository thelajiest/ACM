#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    queue<string> Q;
    for (int i = 1; i <= 9; i++) {
        Q.push(string{char('0' + i)});
    }
    while (!Q.empty()) {
        auto x = Q.front();
        K--;
        if (K == 0) {
            cout << x << endl;
            break;
        }
        Q.pop();
        auto last_num = x.back();
        if (last_num != '0') Q.push(x + string{char(last_num - 1)});
        Q.push(x + string{char(last_num)});
        if (last_num != '9') Q.push(x + string{char(last_num + 1)});
    }

    return 0;
}