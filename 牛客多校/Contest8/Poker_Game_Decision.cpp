#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using VI = vector<int>;
using pii = pair<int, int>;
struct card {
    // S->0, H->1, D->2, C->3
    int suit;
    int rank;
    card() = default;
    card(std::string s) {
        assert(s.size() == 2);
        swap(s[0], s[1]);
        suit = s[0] == 'S' ? 0 : s[0] == 'H' ? 1 : s[0] == 'D' ? 2 : 3;
        rank = s[1] <= '9'   ? s[1] - '0'
               : s[1] == 'T' ? 10
               : s[1] == 'J' ? 11
               : s[1] == 'Q' ? 12
               : s[1] == 'K' ? 13
                             : 14;
    }
    card(int id) {
        suit = id / 13;
        rank = id % 13 + 2;
    }
    int id() { return suit * 13 + rank - 2; }
    bool operator<(card oth) const { return rank < oth.rank; }
};

std::vector<int> eval(std::vector<card> a) {
    assert(a.size() == 5);
    sort(a.begin(), a.end());
    std::set<int> suits;
    for (const auto &c : a) suits.insert(c.suit);
    if (suits.size() == 1 and a.back().rank - a.front().rank == 4) {
        if (a.back().rank == 14)
            return {9};
        else
            return {8, a.back().rank};
    }
    if (suits.size() == 1 and a.back().rank == 14 and a[3].rank == 5) {
        return {8, 5};
    }
    if (a[0].rank == a[3].rank or a[1].rank == a[4].rank) {
        bool tmp = a[0].rank == a[3].rank;
        return {7, tmp ? a[0].rank : a[4].rank, tmp ? a[4].rank : a[0].rank};
    }
    if ((a[0].rank == a[2].rank and a[3].rank == a[4].rank) or
        (a[2].rank == a[4].rank and a[0].rank == a[1].rank)) {
        bool tmp = a[0].rank == a[2].rank;
        return {6, tmp ? a[0].rank : a[4].rank, tmp ? a[4].rank : a[0].rank};
    }
    if (suits.size() == 1) {
        return {5, a[4].rank, a[3].rank, a[2].rank, a[1].rank, a[0].rank};
    }
    bool straight = true;
    for (int i = 0; i < 4; i++) straight &= a[i + 1].rank - a[i].rank == 1;
    if (straight) {
        return {4, a[4].rank};
    }
    if (a[0].rank == 2 and a[1].rank == 3 and a[2].rank == 4 and
        a[3].rank == 5 and a[4].rank == 14) {
        return {4, 5};
    }
    if (a[0].rank == a[2].rank) {
        return {3, a[0].rank, a[4].rank, a[3].rank};
    }
    if (a[1].rank == a[3].rank) {
        return {3, a[1].rank, a[4].rank, a[0].rank};
    }
    if (a[2].rank == a[4].rank) {
        return {3, a[2].rank, a[1].rank, a[0].rank};
    }
    if (a[0].rank == a[1].rank) {
        if (a[2].rank == a[3].rank) return {2, a[2].rank, a[0].rank, a[4].rank};
        if (a[3].rank == a[4].rank) return {2, a[3].rank, a[0].rank, a[2].rank};
    }
    if (a[1].rank == a[2].rank) {
        if (a[3].rank == a[4].rank) return {2, a[3].rank, a[1].rank, a[0].rank};
    }
    if (a[0].rank == a[1].rank) {
        return {1, a[0].rank, a[4].rank, a[3].rank, a[2].rank};
    }
    if (a[1].rank == a[2].rank) {
        return {1, a[1].rank, a[4].rank, a[3].rank, a[0].rank};
    }
    if (a[2].rank == a[3].rank) {
        return {1, a[2].rank, a[4].rank, a[1].rank, a[0].rank};
    }
    if (a[3].rank == a[4].rank) {
        return {1, a[3].rank, a[2].rank, a[1].rank, a[0].rank};
    }
    return {0, a[4].rank, a[3].rank, a[2].rank, a[1].rank, a[0].rank};
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int _;
    cin >> _;
    while (_--) {
        string aa, bb;
        cin >> aa >> bb;

        vector<card> p(6);
        vector<card> a(2), b(2);
        vector<card> A, B;
        A.reserve(6), B.reserve(6);
        a[0] = card(aa), a[1] = card(bb);
        cin >> aa >> bb;
        b[0] = card(aa), b[1] = card(bb);
        for (int i = 0; i < 6; i++) {
            cin >> aa;
            p[i] = card(aa);
        }
        function<int(int, int)> dfs = [&](int turn, int state) -> int {
            if (state == (1 << 6) - 1) {
                auto C = a, D = b;
                copy(begin(A), end(A), back_inserter(C));
                copy(begin(B), end(B), back_inserter(D));
                auto aaa = eval(C), bbb = eval(D);
                auto compare = [&](vector<int> a, vector<int> b) -> int {
                    if (a > b) return 1;
                    if (a < b) return 3;
                    return 2;
                };
                auto ans = compare(aaa, bbb);
                return ans;
            } else {
                int one(0), two(0), three(0);
                for (int i = 0; i < 6; i++) {
                    if (!((state >> i) & 1)) {
                        if (turn == 1) {
                            A.push_back(p[i]);
                        } else
                            B.push_back(p[i]);
                        int q;
                        q = dfs(-turn, state | (1 << i));
                        if (turn == 1) {
                            A.pop_back();
                        } else
                            B.pop_back();
                        if (q == 3) one++;
                        if (q == 2) two++;
                        if (q == 1) three++;
                        if (turn == 1 && three) return 1;
                        if (turn == -1 && one) return 3;
                    }
                }
                if (turn == 1) {
                    if (three) return 1;
                    if (two) return 2;
                    if (one) return 3;
                } else {
                    if (one) return 3;
                    if (two) return 2;
                    if (three) return 1;
                }
                return 1;
            }
        };
        int q = dfs(1, 0);
        if (q == 1) cout << "Alice\n";
        if (q == 2) cout << "Draw\n";
        if (q == 3) cout << "Bob\n";
    }
}
