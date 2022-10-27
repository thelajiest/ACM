/*妳的愛是盃太濃的咖啡*/
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 7;
char s[MAX_N], t[MAX_N];
int sum[MAX_N];
int T, n;

char get_char(char b) {
    if (b == 'b') {
        return 'c';
    } else {
        return 'b';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        string buf;
        cin >> s >> t;
        n = strlen(s);
        for (int i = 0; i < n; ++i) {
            sum[i] = (s[i] == t[i]);
            if (i) sum[i] += sum[i - 1];
        }
        cout << "Case " << cas << ": ";
        int cnt = 0, dec = 0, i = 0;
        for (; i < n && cnt <= (n - 1 - i) - (sum[n - 1] - sum[i]); ++i) {
            assert(cnt >= 0);
            if (s[i] == t[i]) {
                cout << 'a';
                buf = buf + 'a';
                continue;
            }
            if ((s[i] != 'a') && (t[i] != 'a')) {
                cout << 'a';
                buf = buf + 'a';
                continue;
            }
            if (s[i] == 'a') {
                if (dec < 0) {
                    ++dec;
                    --cnt;
                    cout << 'a';
                    buf = buf + 'a';
                } else {
                    if ((n - 1 - i) - (sum[n - 1] - sum[i]) > cnt) {
                        ++dec;
                        ++cnt;
                        cout << 'a';
                        buf = buf + 'a';
                    } else {
                        if (t[i] != 'b') {
                            cout << 'b';
                            buf = buf + 'b';
                        } else {
                            if (dec > 0) {
                                --dec;
                                --cnt;
                                cout << 'b';
                                buf = buf + 'b';
                            } else {
                                cout << 'c';
                                buf = buf + 'c';
                            }
                        }
                    }
                }
            } else {
                if (dec > 0) {
                    --dec;
                    --cnt;
                    cout << 'a';
                    buf = buf + 'a';
                } else {
                    if ((n - 1 - i) - (sum[n - 1] - sum[i]) > cnt) {
                        --dec;
                        ++cnt;
                        cout << 'a';
                        buf = buf + 'a';
                    } else {
                        if (s[i] != 'b') {
                            cout << 'b';
                            buf = buf + 'b';
                        } else {
                            if (dec < 0) {
                                ++dec;
                                --cnt;
                                cout << 'b';
                                buf = buf + 'b';
                            } else {
                                cout << 'c';
                                buf = buf + 'c';
                            }
                        }
                    }
                }
            }
        }
        for (; i < n; ++i) {
            char now = (dec > 0 ? t[i] : s[i]);
            if (s[i] == t[i]) now = 'a';
            cout << now;
        }
        cout << "\n";
    }
    return 0;
}