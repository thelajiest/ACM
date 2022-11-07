#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    getline(cin, n);
    int nn = 0;
    for (int i = 0; i < n.size(); i++) nn = nn * 10 + (n[i] - '0');
    for (int i = 1; i <= nn; i++) {
        string s;
        getline(cin, s);
        int len = s.size();
        string res;
        if (len > 1) {
            for (int j = 0, pos; j < len; j = pos) {
                pos = j;
                if (s[pos] != ':' && s[pos] != '-') {
                    res += s[pos];
                    pos++;
                    continue;
                }
                if (s[j] == ':' || s[j] == '-') {
                    while (pos < len && (s[pos] == ':' || s[pos] == '-')) {
                        pos++;
                    }
                    string gao;
                    for (int k = j; k < pos; k++) {
                        if (k < pos - 1) {
                            gao += s[k];
                            gao += " ";
                        } else
                            gao += s[k];
                    }
                    if (j > 0 && s[j - 1] != ' ') gao = " " + gao;
                    if (pos < len && s[pos] != ' ') gao += " ";
                    res += gao;
                }
            }
            cout << res << '\n';
        } else
            cout << s << '\n';
    }

    return 0;
}