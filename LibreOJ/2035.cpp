#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

// const int Inf = -1u >> 1;
const size_t Size = 3e3 + 5;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> T input() {
    T res = 0; char c = getchar(); bool nega = 0;
    while(c > '9' || c < '0') {if(c == '-') nega = 1; c = getchar();}
    while(c >= '0' && c <= '9') {res = res * 10 - 48 + c, c = getchar();}
    return nega? -res : res;
}

int n, m;

long long f[Size][Size];
long long a[Size];
long long s[Size];
int q[Size], front, back;

inline int fig(int i, int j, int k) {
    return f[k][j - 1] + std::pow(s[i] - s[k], 2);
}

bool judge(int i, int j, int k, int t) {
    return (s[k] - s[i]) * (f[i][t] + s[i] * s[i] - f[j][t] - s[j] * s[j])
        <= (s[i] - s[j]) * (f[k][t] + s[k] * s[k] - f[i][t] - s[i] * s[i]);
}

int main() {
    n = input<int>(), m = input<int>();

    for(int i = 1; i <= n; ++i) {
        a[i] = input<long long>();
        s[i] = s[i - 1] + a[i];
        f[i][1] = std::pow(s[i], 2);
    }

    for(int i = 2; i <= m; ++i) {
        q[front = 0] = i - 1, back = 1;
        for(int j = i; j <= n; ++j) {
            while(front + 1 < back && fig(j, i, q[front]) > fig(j, i, q[front + 1])) ++front;
            f[j][i] = fig(j, i, q[front]);
            while(front + 1 < back && judge(j, q[back - 2], q[back - 1], i - 1)) --back;
            q[back++] = j;
        }
    }

    printf("%lld\n", f[n][m] * m - s[n] * s[n]);

    return 0;
}
