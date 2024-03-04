#include <bits/stdc++.h>

using floatType = double;

/*---------------- constant ---------------------*/
constexpr int W = 192;
constexpr int MAXN = 100;
constexpr int MAXK = 10;
constexpr int MAXT = 1000;
constexpr int MAXR = 10;
constexpr uint32_t SEED = 229;
/*---------------- constant ---------------------*/

/*---------------- tool code ---------------------*/
std::mt19937 seed(SEED);
struct Timer {
    std::chrono::high_resolution_clock::time_point st;

    Timer() { reset(); }

    void reset() { st = std::chrono::high_resolution_clock::now(); }

    std::chrono::milliseconds::rep elapsed() {
        auto ed = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(ed - st)
            .count();
    }
};

inline int randomInt(int l, int r) {
    // return Int [l,r);
    std::uniform_int_distribution<int> RNG(l, r - 1);
    return RNG(seed);
}

inline floatType randomFloat(floatType l, floatType r) {
    // return Int [l,r];
    std::uniform_real_distribution<floatType> RNG(l, r);
    return RNG(seed);
}

void ioSet(size_t precision) {
    std::cout << std::fixed << std::setprecision(precision);
    std::cerr << std::fixed << std::setprecision(precision);
}

/*---------------- tool code ---------------------*/

/*---------------- data ---------------------*/
int N, K, T, R;
/*
User number N
Cell number K
TTI number T
RBG number R
*/

std::vector<floatType> s0[MAXT + 1][MAXK + 1][MAXR + 1];
/*
    s0[t][k][r][n]
    denoting the initial SINR on RBG r of cell k at TTI t for NO.user
*/
void readS0() {
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < R; k++) {
                s0[i][j][k].resize(N);
                for (int t = 0; t < N; t++) {
                    std::cin >> s0[i][j][k][t];
                }
            }
        }
    }

    return;
}

std::vector<floatType> d[MAXK + 1][MAXR + 1][MAXN + 1];
/*
    d[k][r][m][n]
    Interference factors
*/
void readD() {
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < R; j++) {
            for (int k = 0; k < N; k++) {
                s0[i][j][k].resize(N);
                for (int t = 0; t < N; t++) {
                    std::cin >> s0[i][j][k][t];
                }
            }
        }
    }

    return;
}

struct Frame {
    int id;            // frame ID
    int tbs;           // TBS
    int userID;        //  user ID it belongs to,
    int tBegin, tEnd;  // begin time and end time

    void input() {
        int _id, _tbs, _userID, _t0, _td;
        std::cin >> _id >> _tbs >> _userID >> _t0 >> _td;

        id = _id;
        tbs = _tbs;
        userID = _userID;
        tBegin = _t0;
        tEnd = _t0 + _td - 1;

        return;
    }
};
int J;  // number of frame
std::vector<Frame> frame;
std::vector<floatType> p[MAXT + 1][MAXK + 1][MAXR + 1];
std::vector<floatType> s[MAXT + 1][MAXK + 1][MAXR + 1];

void inputAllData() {
    std::cin >> N >> K >> T >> R;
    readS0();
    readD();

    std::cin >> J;
    frame.resize(J);

    for (int i = 0; i < J; i++) {
        frame[i].input();
    }

    for (int i = 0; i < T; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < R; k++) {
                p[i][j][k].resize(N);
                s[i][j][k].resize(N);
            }
        }
    }
    return;
}

/*---------------- data ---------------------*/

/*---------------- algorithm ---------------------*/

floatType solveScore(const Frame& f) {
    for (int t = 0; t < T; t++) {
        for (int k = 0; k < K; k++) {
            for (int r = 0; r < R; r++) {
                for (int n = 0; n < N; n++) {
                    floatType diff = 1;
                    for (int m = 0; m < N; m++) {
                        if (m == n) continue;
                        diff *= std::exp(d[k][r][m][n] * (p[t][k][r][m] > 0));
                    }
                }
            }
        }
    }

    return 0;
}

/*---------------- algorithm ---------------------*/

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> a;
    ioSet(6);
    inputAllData();
    return 0;
}