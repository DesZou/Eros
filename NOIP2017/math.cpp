#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

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
    T r(0); char c(getchar()); bool n(false);
    while(c > '9' || c < '0') {if(c == '-') n = true; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

long long a, b, x, y;

template<class T> void ex_gcd(T a, T b, T &x, T &y) {
    if(!b) {
        x = 1, y = 0;
    } else {
        ex_gcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

int main() {
    // freopen("math.in", "r", stdin);
    // freopen("math.out", "w", stdout);

    a = input<long long>(), b = input<long long>();

    ex_gcd(a, b, x, y);

    x = (x % b + b) % b;
    y = (y % a + a) % a;

    printf("%lld\n", x * a - b + y * b - a - 1);

    return 0;
}
