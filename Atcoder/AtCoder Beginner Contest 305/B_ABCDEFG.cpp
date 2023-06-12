#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    std::string s = "A###B#C####D#E#####F#########G";

    char p, q;
    std::cin >> p >> q;

    int pos1 = s.find(p);
    int pos2 = s.find(q);
    if (pos1 > pos2) std::swap(pos1, pos2);

    std::cout << std::count(begin(s) + pos1, begin(s) + pos2, '#');
    return 0;
}