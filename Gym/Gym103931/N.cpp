#include <bits/stdc++.h>
using namespace std;

string a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> a >> b;
    if (a == b) {
        cout << a << '=' << b << endl;
    } else if (a < b) {
        cout << a << '<' << b << endl;
    } else {
        cout << a << '>' << b << endl;
    }

    return 0;
}
