#include <cstdio>
#include <iostream>
const int N = 5E5 + 10;
int c[N];
int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    for (int i = 1, t; i <= n; i++) {
        scanf("%d", &t);
        c[t]++;
    }
    for (int i = 1; i <= x; i++) {
        c[i] += c[i - 1] / i;
        c[i - 1] = c[i - 1] % i;
    }
    for (int i = 0; i <= x; i++) {
        if (c[i] != 0 && i < x) {
            std::cout << "No";
            return 0;
        }
        if (c[i] < 1 && i == x) {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";
}
