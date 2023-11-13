#include <bits/stdc++.h>

using i64 = std::int64_t;

struct Node {
    int x, y, w;
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    std::vector<Node> useful;

    int x, y, w;
    int size;
    int max = 0;
    int max2 = 0;

    int t, i, j, tt;

    std::vector<int> del;
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            std::cin >> x >> y >> w;

            size = useful.size();
            max = 0;
            for (t = 0; t < size; t++) {
                for (i = 0; i < size; i++) {
                    for (j = 0; j < size; j++) {
                        if (useful[t].x != useful[i].x &&
                            useful[t].y != useful[j].y)
                            max = std::max(max, useful[t].w);
                    }
                }
            }

            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    if (useful[t].x != useful[i].x &&
                        useful[t].y != useful[j].y)
                        max2 = std::max(max2, useful[t].w);
                }
            }
        }
    }
    return 0;
}