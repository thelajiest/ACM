#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 7;
char s[MAX_N];
int cnt[MAX_N];
int h, w;

int main() {
    ios::sync_with_stdio(false);
    cin >> h >> w;
    for (int i = 0; i < h; ++i) {
        cin >> s;
        for (int j = 0; j < w; ++j) {
            if (s[j] == '#') ++cnt[j];
        }
    }
    for (int j = 0; j < w; ++j) cout << cnt[j] << " ";
    cout << "\n";
    return 0;
}