#include <bits/stdc++.h>

using i64 = std::int64_t;

struct dp_hull {
    // dp_hull enables you to do the following two operations in amortized O(log
    // n) time:
    // 1. Insert a pair (a_i, b_i) into the structure
    // 2. For any value of x, query the maximum value of a_i * x + b_i
    // All values a_i, b_i, and x can be positive or negative.
    struct point {
        i64 x, y;
        point() : x(0), y(0) {}
        point(i64 _x, i64 _y) : x(_x), y(_y) {}
    };
    struct segment {
        point p;
        mutable point next_p;
        segment(point _p = {0, 0}, point _next_p = {0, 0})
            : p(_p), next_p(_next_p) {}
        bool operator<(const segment &other) const {
            if (p.y == std::numeric_limits<i64>::max() / 2)
                return p.x * (other.next_p.x - other.p.x) <=
                       other.p.y - other.next_p.y;
            return std::make_pair(p.x, p.y) <
                   std::make_pair(other.p.x, other.p.y);
        }
    };
    std::set<segment> segments;
    int size() const { return segments.size(); }
    std::set<segment>::iterator prev(std::set<segment>::iterator it) const {
        return it == segments.begin() ? it : --it;
    }
    std::set<segment>::iterator next(std::set<segment>::iterator it) const {
        return it == segments.end() ? it : ++it;
    }
    static i64 floor_div(i64 a, i64 b) {
        return a / b - ((a ^ b) < 0 && a % b != 0);
    }
    static bool bad_middle(const point &a, const point &b, const point &c) {
        return floor_div(a.y - b.y, b.x - a.x) >=
               floor_div(b.y - c.y, c.x - b.x);
    }
    bool bad(std::set<segment>::iterator it) const {
        return it != segments.begin() && next(it) != segments.end() &&
               bad_middle(prev(it)->p, it->p, next(it)->p);
    }
    void insert(const point &p) {
        std::set<segment>::iterator next_it = segments.lower_bound(segment(p));
        if (next_it != segments.end() && p.x == next_it->p.x) return;
        if (next_it != segments.begin()) {
            std::set<segment>::iterator prev_it = prev(next_it);
            if (p.x == prev_it->p.x)
                segments.erase(prev_it);
            else if (next_it != segments.end() &&
                     bad_middle(prev_it->p, p, next_it->p))
                return;
        }
        std::set<segment>::iterator it =
            segments.insert(next_it, segment(p, p));
        while (bad(prev(it))) segments.erase(prev(it));
        while (bad(next(it))) segments.erase(next(it));
        if (it != segments.begin()) prev(it)->next_p = it->p;
        if (next(it) != segments.end()) it->next_p = next(it)->p;
    }

    void insert(i64 a, i64 b) { insert(point(a, b)); }
    // Queries the maximum value of ax + b.
    i64 query(i64 x) const {
        assert(size() > 0);
        std::set<segment>::iterator it = segments.upper_bound(
            segment(point(x, std::numeric_limits<i64>::max() / 2)));
        return it->p.x * x + it->p.y;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<i64> t(n + 1), dt(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> t[i];
        dt[i] = dt[i - 1] + t[i];
    }

    std::vector<i64> dp(n + 1);

    dp_hull Hull;
    Hull.insert(0, -k);

    for (int i = 1; i <= n; i++) {
        dp[i] = -Hull.query(t[i]) + 1LL * i * t[i] - dt[i];
        Hull.insert(i, -(dp[i] + k + dt[i]));
    }

    std::cout << dp[n] << std::endl;

    return 0;
}