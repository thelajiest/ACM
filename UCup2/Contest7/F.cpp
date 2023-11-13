#include <bits/stdc++.h>
using i64 = std::int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int p, q;
    std::cin >> p >> q;

    for (int x = 1; x <= 10; x++) {
        for (int y = x; y <= 10; y++) {
            bool a = x * 5 <= y * 4;
            bool b = x * 4 >= y * 3;
            if (a && b) {
                std::cerr << x << " " << y << std::endl;
            }
        }
    }
    // assert(p != 3 && q != 4);x
    if (p == 0) {
        std::cout << "1 1" << std::endl;
        std::cout << "." << std::endl;
        return 0;
    }
    // for (int p = 1; p <= 10; p++) {
    //     for (int q = p; q <= 10; q++) {
    // if (std::gcd(p, q) != 1) continue;
    if (5 * p > 4 * q) {
        std::cout << "-1 -1" << std::endl;
    } else {
        if (p == 2 && q == 3) {
            std::cout << "4 6" << std::endl;
            std::cout << ".####.\n##..##\n##..##\n.####." << std::endl;
            return 0;
        }
        if (p == 7 && q == 10) {
            std::cout << "4 5" << std::endl;
            std::cout << ".###.\n##.##\n##.##\n.###." << std::endl;
            return 0;
        }

        if (p == 3 && q == 4) {
            std::cout << "4 4" << std::endl;
            std::cout << ".###\n##.#\n##.#\n.###" << std::endl;
            return 0;
        }

        if (p == 5 && q == 7) {
            std::cout << "4 14" << std::endl;
            std::cout << ".###..###..###\n##.####.####.#\n##.####.####.#\n.###."
                         ".###..###"
                      << std::endl;
            return 0;
        }

        if (p == 4 && q == 5) {
            std::cout << "5 5" << std::endl;
            std::cout << "###.#\n#.###\n####.\n##.##\n.####" << std::endl;
            return 0;
        }
        if (p == 7 && q == 9) {
            std::cout << "-1 -1" << std::endl;
        }
        bool find = false;
        for (int k = 1; k <= 500; k++) {
            for (int d = 0; 3 * k + 1 + d <= 1000; d++) {
                int x = 2 * k;
                int y = 3 * k + 1 + d;

                int g = std::gcd(x, y);
                x /= g;
                y /= g;
                if (x == p && y == q) {
                    std::cout << 1 << " " << 3 * k + 1 + d << std::endl;
                    find = true;
                    for (int i = 0; i < d + 1; i++) std::cout << ".";
                    for (int i = 0; i < k; i++) {
                        std::cout << "##.";
                    }
                    return 0;
                }
            }
        }
        // assert(find == true);
    }
    //     }
    // }
    return 0;
}