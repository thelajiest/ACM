#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#define Mod 1000000007
#define eps 1e-8
#define lll __int64
#define ll long long
using namespace std;
#define N 100007
#define MAXV 505

// 三维点
struct pt {
    double x, y, z;
    pt() {}
    pt(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    pt operator-(const pt p1) { return pt(x - p1.x, y - p1.y, z - p1.z); }
    pt operator*(pt p) {
        return pt(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }                                                               // 叉乘
    double operator^(pt p) { return x * p.x + y * p.y + z * p.z; }  // 点乘
};

// pt operator - (const pt p,const pt p1){return pt(p.x - p1.x, p.y - p1.y, p.z
// - p1.z);} pt operator ** (pt p,pt p1){return pt(p.y*p1.z-p.z*p1.y,
// p.z*p1.x-p.x*p1.z, p.x*p1.y-p.y*p1.x);}        //叉乘 double operator ^^ (pt
// p1,pt p){return p1.x*p.x+p1.y*p.y+p1.z*p.z;}

struct _3DCH {
    struct fac {
        int a, b, c;  // 表示凸包一个面上三个点的编号
        bool ok;      // 表示该面是否属于最终凸包中的面
    };

    int n;       // 初始点数
    pt P[MAXV];  // 初始点

    int cnt;          // 凸包表面的三角形数
    fac F[MAXV * 8];  // 凸包表面的三角形

    int to[MAXV][MAXV];

    double vlen(pt a) {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }  // 向量长度
    double area(pt a, pt b, pt c) {
        return vlen((b - a) * (c - a));
    }  // 三角形面积*2
    double volume(pt a, pt b, pt c, pt d) {
        return (b - a) * (c - a) ^ (d - a);
    }  // 四面体有向体积*6

    // 正：点在面同向
    double ptof(pt &p, fac &f) {
        pt m = P[f.b] - P[f.a], n = P[f.c] - P[f.a], t = p - P[f.a];
        return (m * n) ^ t;
    }
    pt pvec(fac s) {
        pt k1 = (P[s.a] - P[s.b]), k2 = (P[s.b] - P[s.c]);
        return (k1 * k2);
    }
    double ptoplane(pt p, fac s) {
        return fabs(pvec(s) ^ (p - P[s.a])) / vlen(pvec(s));
    }

    void deal(int p, int a, int b) {
        int f = to[a][b];
        fac add;
        if (F[f].ok) {
            if (ptof(P[p], F[f]) > eps)
                dfs(p, f);
            else {
                add.a = b, add.b = a, add.c = p, add.ok = 1;
                to[p][b] = to[a][p] = to[b][a] = cnt;
                F[cnt++] = add;
            }
        }
    }

    void dfs(int p, int cur) {
        F[cur].ok = 0;
        deal(p, F[cur].b, F[cur].a);
        deal(p, F[cur].c, F[cur].b);
        deal(p, F[cur].a, F[cur].c);
    }

    bool same(int s, int t) {
        pt &a = P[F[s].a], &b = P[F[s].b], &c = P[F[s].c];
        return fabs(volume(a, b, c, P[F[t].a])) < eps &&
               fabs(volume(a, b, c, P[F[t].b])) < eps &&
               fabs(volume(a, b, c, P[F[t].c])) < eps;
    }

    // 构建三维凸包
    void construct() {
        cnt = 0;
        if (n < 4) return;

        /*********此段是为了保证前四个点不公面，若已保证，可去掉********/
        bool sb = 1;
        // 使前两点不公点
        for (int i = 1; i < n; i++) {
            if (vlen(P[0] - P[i]) > eps) {
                swap(P[1], P[i]);
                sb = 0;
                break;
            }
        }
        if (sb) return;

        sb = 1;
        // 使前三点不公线
        for (int i = 2; i < n; i++) {
            if (vlen((P[0] - P[1]) * (P[1] - P[i])) > eps) {
                swap(P[2], P[i]);
                sb = 0;
                break;
            }
        }
        if (sb) return;

        sb = 1;
        // 使前四点不共面
        for (int i = 3; i < n; i++) {
            if (fabs((P[0] - P[1]) * (P[1] - P[2]) ^ (P[0] - P[i])) > eps) {
                swap(P[3], P[i]);
                sb = 0;
                break;
            }
        }
        if (sb) return;
        /*********此段是为了保证前四个点不公面********/

        fac add;
        for (int i = 0; i < 4; i++) {
            add.a = (i + 1) % 4, add.b = (i + 2) % 4, add.c = (i + 3) % 4,
            add.ok = 1;
            if (ptof(P[i], add) > 0) swap(add.b, add.c);
            to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
            F[cnt++] = add;
        }

        for (int i = 4; i < n; i++) {
            for (int j = 0; j < cnt; j++) {
                if (F[j].ok && ptof(P[i], F[j]) > eps) {
                    dfs(i, j);
                    break;
                }
            }
        }
        int tmp = cnt;
        cnt = 0;
        for (int i = 0; i < tmp; i++) {
            if (F[i].ok) {
                F[cnt++] = F[i];
            }
        }
    }

    // 表面积
    double area() {
        double ret = 0.0;
        for (int i = 0; i < cnt; i++) {
            ret += area(P[F[i].a], P[F[i].b], P[F[i].c]);
        }
        return ret / 2.0;
    }

    // 体积
    double volume() {
        pt O(0, 0, 0);
        double ret = 0.0;
        for (int i = 0; i < cnt; i++) {
            ret += volume(O, P[F[i].a], P[F[i].b], P[F[i].c]);
        }
        return fabs(ret / 6.0);
    }

    pt BaryCenter() {
        pt O(0, 0, 0);
        double ret = 0.0, sumvolume = 0.0, sumx = 0.0, sumy = 0.0, sumz = 0.0;
        for (int i = 0; i < cnt; i++) {
            double Vol = volume(O, P[F[i].a], P[F[i].b], P[F[i].c]);
            sumvolume += Vol;
            sumx += (P[F[i].a].x + P[F[i].b].x + P[F[i].c].x) * Vol;
            sumy += (P[F[i].a].y + P[F[i].b].y + P[F[i].c].y) * Vol;
            sumz += (P[F[i].a].z + P[F[i].b].z + P[F[i].c].z) * Vol;
        }
        return pt(sumx / sumvolume / 4, sumy / sumvolume / 4,
                  sumz / sumvolume / 4);
    }

    // 表面三角形数
    int facetCnt_tri() { return cnt; }

    // 表面多边形数
    int facetCnt() {
        int ans = 0;
        for (int i = 0; i < cnt; i++) {
            bool nb = 1;
            for (int j = 0; j < i; j++) {
                if (same(i, j)) {
                    nb = 0;
                    break;
                }
            }
            ans += nb;
        }
        return ans;
    }
};

_3DCH hull, hull2;  // 内有大数组，不易放在函数内

int main() {
    cin >> hull.n;
    for (int i = 0; i < hull.n; i++)
        scanf("%lf%lf%lf", &hull.P[i].x, &hull.P[i].y, &hull.P[i].z);
    hull.construct();

    for (int i = 0; i < hull.cnt; i++) {
        cout << hull.F[i].a << " " << hull.F[i].b << " " << hull.F[i].c << '\n';
    }

    return 0;
}