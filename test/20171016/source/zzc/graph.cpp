#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const int Inf = 0x3f3f3f3f;
const size_t Size = 100 + 5;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(getchar()); bool n(0);
    while(c > '9' || c < '0') {if(c == '-') n = 1; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

struct matrix {
    int elem[Size][Size], len;

    matrix(int x) :len(x) {std::memset(elem, 0x3f, sizeof elem);}

    int& operator()(const int x, const int y) {
        return elem[x][y];
    }

    matrix operator*(matrix &rhs) {
        matrix res(len);
        for(int k = 1; k <= len; ++k)
            for(int i = 1; i <= len; ++i)
                for(int j = 1; j <= len; ++j)
                    chkmin(res(i, j), elem[i][k] + rhs(k, j));
        return res;
    }
};

int n, m, e;

matrix power(matrix a, int b) {
    matrix res = a; --b;
    while(b) {
        if(b & 1) res = res * a;
        a = a * a, b >>= 1;
    } return res;
}

int main() {
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);

    n = input<int>(), m = input<int>(), e = input<int>();

    static matrix ans(n);

    for(int i = 1, u, v, w; i <= m; ++i) {
        u = input<int>(), v = input<int>(), w = input<int>();
        ans(u, v) = ans(v, u) = w;
    }

    ans = power(ans, e);

    for(int q = input<int>(), u, v; q; --q) {
        u = input<int>(), v = input<int>();
        printf("%d\n", ans(u, v) == Inf? -1 : ans(u, v));
    }

    return 0;
}
