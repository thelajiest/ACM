#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define int ll

#define rng(i, a, b) for (int i = int(a); i < int(b); i++)
#define rep(i, b) rng(i, 0, b)
#define gnr(i, a, b) for (int i = int(b) - 1; i >= int(a); i--)
#define per(i, b) gnr(i, 0, b)
#define pb push_back
#define eb emplace_back
#define a first
#define b second
#define bg begin()
#define ed end()
#define all(x) x.bg, x.ed
#define si(x) int(x.size())
#ifdef LOCAL
#define dmp(x) cerr << __LINE__ << " " << #x << " " << x << endl
#else
#define dmp(x) void(0)
#endif

template <class t, class u>
bool chmax(t& a, u b) {
    if (a < b) {
        a = b;
        return true;
    } else
        return false;
}
template <class t, class u>
bool chmin(t& a, u b) {
    if (b < a) {
        a = b;
        return true;
    } else
        return false;
}

template <class t>
using vc = vector<t>;
template <class t>
using vvc = vc<vc<t>>;

using pi = pair<int, int>;
using vi = vc<int>;

template <class t, class u>
ostream& operator<<(ostream& os, const pair<t, u>& p) {
    return os << "{" << p.a << "," << p.b << "}";
}

template <class t>
ostream& operator<<(ostream& os, const vc<t>& v) {
    os << "{";
    for (auto e : v) os << e << ",";
    return os << "}";
}

#define mp make_pair
#define mt make_tuple
#define one(x) memset(x, -1, sizeof(x))
#define zero(x) memset(x, 0, sizeof(x))
#ifdef LOCAL
void dmpr(ostream& os) { os << endl; }
template <class T, class... Args>
void dmpr(ostream& os, const T& t, const Args&... args) {
    os << t << " ";
    dmpr(os, args...);
}
#define dmp2(...) dmpr(cerr, __LINE__, ##__VA_ARGS__)
#else
#define dmp2(...) void(0)
#endif

using uint = unsigned;
using ull = unsigned long long;

template <class t, size_t n>
ostream& operator<<(ostream& os, const array<t, n>& a) {
    return os << vc<t>(all(a));
}

template <int i, class T>
void print_tuple(ostream&, const T&) {}

template <int i, class T, class H, class... Args>
void print_tuple(ostream& os, const T& t) {
    if (i) os << ",";
    os << get<i>(t);
    print_tuple<i + 1, T, Args...>(os, t);
}

template <class... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    os << "{";
    print_tuple<0, tuple<Args...>, Args...>(os, t);
    return os << "}";
}

ll read() {
    ll i;
    cin >> i;
    return i;
}

vi readvi(int n, int off = 0) {
    vi v(n);
    rep(i, n) v[i] = read() + off;
    return v;
}

pi readpi(int off = 0) {
    int a, b;
    cin >> a >> b;
    return pi(a + off, b + off);
}

template <class t>
void print_single(t x, int suc = 1) {
    cout << x;
    if (suc == 1) cout << "\n";
    if (suc == 2) cout << " ";
}

template <class t, class u>
void print_single(const pair<t, u>& p, int suc = 1) {
    print_single(p.a, 2);
    print_single(p.b, suc);
}

template <class T>
void print_single(const vector<T>& v, int suc = 1) {
    rep(i, v.size()) print_single(v[i], i == int(v.size()) - 1 ? suc : 2);
}

template <class T>
void print_offset(const vector<T>& v, ll off, int suc = 1) {
    rep(i, v.size()) print_single(v[i] + off, i == int(v.size()) - 1 ? suc : 2);
}

template <class T, size_t N>
void print_single(const array<T, N>& v, int suc = 1) {
    rep(i, N) print_single(v[i], i == int(N) - 1 ? suc : 2);
}

template <class T>
void print(const T& t) {
    print_single(t);
}

template <class T, class... Args>
void print(const T& t, const Args&... args) {
    print_single(t, 2);
    print(args...);
}

string readString() {
    string s;
    cin >> s;
    return s;
}

template <class T>
T sq(const T& t) {
    return t * t;
}

void YES(bool ex = true) {
    cout << "YES\n";
    if (ex) exit(0);
#ifdef LOCAL
    cout.flush();
#endif
}
void NO(bool ex = true) {
    cout << "NO\n";
    if (ex) exit(0);
#ifdef LOCAL
    cout.flush();
#endif
}
void Yes(bool ex = true) {
    cout << "Yes\n";
    if (ex) exit(0);
#ifdef LOCAL
    cout.flush();
#endif
}
void No(bool ex = true) {
    cout << "No\n";
    if (ex) exit(0);
#ifdef LOCAL
    cout.flush();
#endif
}
// #define CAPITAL
/*
void yes(bool ex=true){
        #ifdef CAPITAL
        cout<<"YES"<<"\n";
        #else
        cout<<"Yes"<<"\n";
        #endif
        if(ex)exit(0);
        #ifdef LOCAL
        cout.flush();
        #endif
}
void no(bool ex=true){
        #ifdef CAPITAL
        cout<<"NO"<<"\n";
        #else
        cout<<"No"<<"\n";
        #endif
        if(ex)exit(0);
        #ifdef LOCAL
        cout.flush();
        #endif
}*/
void possible(bool ex = true) {
#ifdef CAPITAL
    cout << "POSSIBLE"
         << "\n";
#else
    cout << "Possible"
         << "\n";
#endif
    if (ex) exit(0);
#ifdef LOCAL
    cout.flush();
#endif
}
void impossible(bool ex = true) {
#ifdef CAPITAL
    cout << "IMPOSSIBLE"
         << "\n";
#else
    cout << "Impossible"
         << "\n";
#endif
    if (ex) exit(0);
#ifdef LOCAL
    cout.flush();
#endif
}

constexpr ll ten(int n) { return n == 0 ? 1 : ten(n - 1) * 10; }

const ll infLL = LLONG_MAX / 3;

#ifdef int
const int inf = infLL;
#else
const int inf = INT_MAX / 2 - 100;
#endif

int topbit(signed t) { return t == 0 ? -1 : 31 - __builtin_clz(t); }
int topbit(ll t) { return t == 0 ? -1 : 63 - __builtin_clzll(t); }
int topbit(ull t) { return t == 0 ? -1 : 63 - __builtin_clzll(t); }
int botbit(signed a) { return a == 0 ? 32 : __builtin_ctz(a); }
int botbit(ll a) { return a == 0 ? 64 : __builtin_ctzll(a); }
int botbit(ull a) { return a == 0 ? 64 : __builtin_ctzll(a); }
int popcount(signed t) { return __builtin_popcount(t); }
int popcount(ll t) { return __builtin_popcountll(t); }
int popcount(ull t) { return __builtin_popcountll(t); }
int bitparity(ll t) { return __builtin_parityll(t); }
bool ispow2(int i) { return i && (i & -i) == i; }
ll mask(int i) { return (ll(1) << i) - 1; }
ull umask(int i) { return (ull(1) << i) - 1; }
ll minp2(ll n) {
    if (n <= 1)
        return 1;
    else
        return ll(1) << (topbit(n - 1) + 1);
}

bool inc(int a, int b, int c) { return a <= b && b <= c; }

template <class t>
void mkuni(vc<t>& v) {
    sort(all(v));
    v.erase(unique(all(v)), v.ed);
}

ll rand_int(ll l, ll r) {  //[l, r]
    // #ifdef LOCAL
    static mt19937_64 gen;
    /*#else
    static mt19937_64
    gen(chrono::steady_clock::now().time_since_epoch().count()); #endif*/
    return uniform_int_distribution<ll>(l, r)(gen);
}

ll rand_int(ll k) {  //[0,k)
    return rand_int(0, k - 1);
}

template <class t>
void myshuffle(vc<t>& a) {
    rep(i, si(a)) swap(a[i], a[rand_int(0, i)]);
}

template <class t>
int lwb(const vc<t>& v, const t& a) {
    return lower_bound(all(v), a) - v.bg;
}
template <class t>
bool bis(const vc<t>& v, const t& a) {
    return binary_search(all(v), a);
}

vvc<int> readGraph(int n, int m) {
    vvc<int> g(n);
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        // sc.read(a,b);
        a--;
        b--;
        g[a].pb(b);
        g[b].pb(a);
    }
    return g;
}

vvc<int> readTree(int n) { return readGraph(n, n - 1); }

template <class t>
vc<t> presum(const vc<t>& a) {
    vc<t> s(si(a) + 1);
    rep(i, si(a)) s[i + 1] = s[i] + a[i];
    return s;
}
vc<ll> presum(const vi& a) {
    vc<ll> s(si(a) + 1);
    rep(i, si(a)) s[i + 1] = s[i] + a[i];
    return s;
}
// BIT で数列を管理するときに使う (CF850C)
template <class t>
vc<t> predif(vc<t> a) {
    gnr(i, 1, si(a)) a[i] -= a[i - 1];
    return a;
}
template <class t>
vvc<ll> imos(const vvc<t>& a) {
    int n = si(a), m = si(a[0]);
    vvc<ll> b(n + 1, vc<ll>(m + 1));
    rep(i, n) rep(j, m) b[i + 1][j + 1] =
        b[i + 1][j] + b[i][j + 1] - b[i][j] + a[i][j];
    return b;
}

// verify してないや
void transvvc(int& n, int& m) { swap(n, m); }
template <class t, class... Args>
void transvvc(int& n, int& m, vvc<t>& a, Args&... args) {
    assert(si(a) == n);
    vvc<t> b(m, vi(n));
    rep(i, n) {
        assert(si(a[i]) == m);
        rep(j, m) b[j][i] = a[i][j];
    }
    a.swap(b);
    transvvc(n, m, args...);
}
// CF854E
void rotvvc(int& n, int& m) { swap(n, m); }
template <class t, class... Args>
void rotvvc(int& n, int& m, vvc<t>& a, Args&... args) {
    assert(si(a) == n);
    vvc<t> b(m, vi(n));
    rep(i, n) {
        assert(si(a[i]) == m);
        rep(j, m) b[m - 1 - j][i] = a[i][j];
    }
    a.swap(b);
    rotvvc(n, m, args...);
}

// ソートして i 番目が idx[i]
// CF850C
template <class t>
vi sortidx(const vc<t>& a) {
    int n = si(a);
    vi idx(n);
    iota(all(idx), 0);
    sort(all(idx), [&](int i, int j) { return a[i] < a[j]; });
    return idx;
}
// vs[i]=a[idx[i]]
// 例えば sortidx で得た idx を使えば単にソート列になって返ってくる
// CF850C
template <class t>
vc<t> a_idx(const vc<t>& a, const vi& idx) {
    int n = si(a);
    assert(si(idx) == n);
    vc<t> vs(n);
    rep(i, n) vs[i] = a[idx[i]];
    return vs;
}
// CF850C
vi invperm(const vi& p) {
    int n = si(p);
    vi q(n);
    rep(i, n) q[p[i]] = i;
    return q;
}

template <class t, class s = t>
s SUM(const vc<t>& a) {
    return accumulate(all(a), s(0));
}

template <class t>
t MAX(const vc<t>& a) {
    return *max_element(all(a));
}

template <class t>
pair<t, int> MAXi(const vc<t>& a) {
    auto itr = max_element(all(a));
    return mp(*itr, itr - a.bg);
}

template <class t>
t MIN(const vc<t>& a) {
    return *min_element(all(a));
}

template <class t>
pair<t, int> MINi(const vc<t>& a) {
    auto itr = min_element(all(a));
    return mp(*itr, itr - a.bg);
}

vi vid(int n) {
    vi res(n);
    iota(all(res), 0);
    return res;
}

template <class S>
void soin(S& s) {
    sort(all(s));
}

template <class S>
S soout(S s) {
    soin(s);
    return s;
}

template <class S>
void rein(S& s) {
    reverse(all(s));
}

template <class S>
S reout(S s) {
    rein(s);
    return s;
}

template <class t, class u>
pair<t, u>& operator+=(pair<t, u>& a, pair<t, u> b) {
    a.a += b.a;
    a.b += b.b;
    return a;
}
template <class t, class u>
pair<t, u>& operator-=(pair<t, u>& a, pair<t, u> b) {
    a.a -= b.a;
    a.b -= b.b;
    return a;
}
template <class t, class u>
pair<t, u> operator+(pair<t, u> a, pair<t, u> b) {
    return mp(a.a + b.a, a.b + b.b);
}
template <class t, class u>
pair<t, u> operator-(pair<t, u> a, pair<t, u> b) {
    return mp(a.a - b.a, a.b - b.b);
}

template <class t>
t gpp(vc<t>& vs) {
    assert(si(vs));
    t res = move(vs.back());
    vs.pop_back();
    return res;
}

template <class t>
void pb(vc<t>& a, const vc<t>& b) {
    a.insert(a.ed, all(b));
}

template <class t>
vc<t> cat(vc<t> a, const vc<t>& b) {
    pb(a, b);
    return a;
}

template <class t, class u>
vc<t>& operator+=(vc<t>& a, u x) {
    for (auto& v : a) v += x;
    return a;
}

template <class t, class u>
vc<t> operator+(vc<t> a, u x) {
    return a += x;
}

template <class t, class u>
vc<t>& operator-=(vc<t>& a, u x) {
    for (auto& v : a) v -= x;
    return a;
}

template <class t, class u>
vc<t>& operator-(vc<t> a, u x) {
    return a -= x;
}

// find the indices of row maxima
// the smallest index is used in case of tie
// f
// の戻り地が小数のときは比較関数のあたりの精度が怪しいが，大体は動くのではないだろうか？
// cmp(i,j,k) = f(i,j)<f(i,k)
//-inf とかを入れて下三角だと思うとかでもいいはず (VERIFY:KUPC2021F)
//-inf の値は全部同じじゃないとダメ (正確には各行で広義単調減少であるべき)
//-inf の扱いに注意
// 例: 数列と凸関数の畳込みで，凸関数の値がない部分を inf と思い込むとする
// このときすべてを inf に丸めると壊れる
// 値がない部分は傾き inf と思う必要がある → int128 (KUPC2021F)
// 最終手段で int128 を召喚
// → f ではなく cmp を与える形式にしたことでこれを回避
// f がいい感じの性質を満たしていないと WA どころか RE でぶっ壊れる
// VERIFY
// Codechef CHEFAOR (needs optimization!)
// Petrozavodsk Camp 2010S Kyiv NU Contest I (D=long double,double で動作確認)
// GCJ 2020 WF D (D=long double)
// CF694F
template <class F>
vi smawk(F cmp, int n, int m) {
    vi ans(n, -1);
    auto upd = [&](int r, int c) {
        if (ans[r] == -1 || cmp(r, ans[r], c)) {
            ans[r] = c;
        }
    };
    auto rec = [&](auto self, int* const rs, int x, int* const cs,
                   int y) -> void {
        const int t = 8;
        if (x <= t || y <= t) {
            rep(i, x) rep(j, y) upd(rs[i], cs[j]);
            return;
        }
        if (x < y) {
            int s = 0;
            rep(i, y) {
                int c = cs[i];
                while (s && cmp(rs[s - 1], cs[s - 1], c)) s--;
                if (s < x) cs[s++] = c;
            }
            y = s;
        }
        auto a = rs + x, b = cs + y;
        int z = 0;
        for (int i = 1; i < x; i += 2) a[z++] = rs[i];
        rep(i, y) b[i] = cs[i];
        self(self, a, z, b, y);
        int k = 0;
        for (int i = 0; i < x; i += 2) {
            int to = i + 1 < x ? ans[rs[i + 1]] : cs[y - 1];
            while (1) {
                upd(rs[i], cs[k]);
                if (cs[k] == to) break;
                k++;
            }
        }
    };
    static int rs[1234567];  // at least n*2
    static int cs[1235467];  // at least max(m,n*2)
    rep(i, n) rs[i] = i;
    rep(i, m) cs[i] = i;
    rec(rec, rs, n, cs, m);
    return ans;
}

// Codechef 2022 August Lunchtime E
vi max_convolution_with_upper_convex(const vi& conv, const vi& a) {
    int n = si(conv), m = si(a);
    auto cmp = [&](int i, int j, int k) {
        assert(j < k);
        if (i < k) return false;
        if (i - j >= n) return true;
        return conv[i - j] + a[j] < conv[i - k] + a[k];
    };
    vi idx = smawk(cmp, n + m - 1, m);
    vi res(n + m - 1);
    rep(i, n + m - 1) res[i] = conv[i - idx[i]] + a[idx[i]];
    return res;
}
// SEERC 2022 L
vi min_convolution_with_lower_convex(vi conv, vi a) {
    for (auto& v : conv) v = -v;
    for (auto& v : a) v = -v;
    vi res = max_convolution_with_upper_convex(conv, a);
    for (auto& v : res) v = -v;
    return res;
}

bool dbg = false;

void slv() {
    int n;
    cin >> n;
    vc<pi> ab(n);
    rep(i, n) { cin >> ab[i].a >> ab[i].b; }
    for (auto& [a, b] : ab) swap(a, b);
    soin(ab);
    for (auto& [a, b] : ab) swap(a, b);
    dmp(ab);

    vi as(n);
    auto dfs = [&](auto self, int l, int r) -> vi {
        if (r - l == 1) {
            vi res(1);
            res[0] = ab[l].a + ab[l].b;
            as[l] = ab[l].a;
            return res;
        } else {
            int m = (l + r) / 2;
            vi q = self(self, l, m);
            vi x(m - l + 1);
            rep(i, m - l) x[i + 1] = x[i] + as[l + i];
            vi y = self(self, m, r);
            vi z = min_convolution_with_lower_convex(x, y);
            rep(i, si(q)) chmin(z[i], q[i]);
            inplace_merge(as.bg + l, as.bg + m, as.bg + r);
            return z;
        }
    };
    vi ans = dfs(dfs, 0, n);
    for (auto v : ans) print(v);
}

signed main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout << fixed << setprecision(20);

    if (dbg) {
        while (1) slv();
    } else {
        // int t;cin>>t;rep(_,t)
        slv();
    }
}
