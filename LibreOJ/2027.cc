/*
 *  libreoj 2027
 *
 *  矩阵树定理求生成树计数这个已经接触过了。
 *  但是辗转相除的高斯消元算是学到了，很好用。
 *  第一次交挂了是因为消元的时候少取了模。
 *  基本思路就是容斥求有多少个公司没有建边，
 *  然后求每次主子式统计答案即可。
 *  时间复杂度 O(2^n n^3) ，能过。
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

const size_t Size = 17 + 2;
const long long Mod = 1e9 + 7;

int n;
long long ans;

std::vector<std::pair<int, int> > e[Size];

struct Matrix {
    long long e[Size * Size];
    int line, col;

    Matrix(int x, int y): line(x), col(y) {
        std::memset(e, 0, sizeof e);
    }

    inline long long& operator()(const int &i, const int &j) {
        return *(e + (i - 1) * col + j - 1);
    }

    void clear() {
        std::memset(e, 0, sizeof e);
    }
};

long long principalMinor(Matrix &a) { // XXX: 辗转消元求主子式必须先去掉一组行列
    long long res = 1; int tmp;
    for(int i = 1; i < a.line; ++i)
        for(int j = i + 1; j < a.line; ++j) while(a(j, i) != 0) {
            tmp = a(i, i) / a(j, i);
            for(int k = i; k < a.col; ++k)
                (a(i, k) -= a(j, k) * tmp % Mod) %= Mod; // 一定要取模
            for(int k = i; k < a.col; ++k)
                std::swap(a(i, k), a(j, k));
            res = -res;
        }
    for(int i = 1; i < a.line; ++i) res = (res * a(i, i)) % Mod;
    return res;
}

int main() {
    std::scanf("%d", &n);

    static Matrix d(n, n);

    int lim = 1 << (n - 1);

    for(int i = 1, l, x, y; i < n; ++i) {
        std::scanf("%d", &l);
        for(int j = 0; j < l; ++j) {
            std::scanf("%d%d", &x, &y);
            e[i].push_back(std::make_pair(x, y));
        }
    }

    for(int u = 1, bit; u < lim; ++u) {
        bit = 0;
        for(int i = 1; i < n; ++i) if((1 << (i - 1)) & u) {
            for(int j = e[i].size() - 1; j >= 0; --j) {
                --d(e[i][j].first, e[i][j].second);
                --d(e[i][j].second, e[i][j].first);
                ++d(e[i][j].first, e[i][j].first);
                ++d(e[i][j].second, e[i][j].second);
            } ++bit;
        }

        ans = (n & 1) ^ (bit & 1) // 容斥判断，看有几个公司没有算
            ? (ans + principalMinor(d)) % Mod
            : (ans - principalMinor(d)) % Mod;

        d.clear();
    }

    std::printf("%lld\n", (ans + Mod) % Mod);

    return 0;
}
