/*
 * luogu2303
 *
 * 莫比乌斯反演。
 * 这种题的要点在于，你可以给式子中的 [gcd(x, y) = k] 除掉一个 k 。
 * 这样就可以变成 [gcd(x/k, y/k) = 1] ，有什么好处呢？ gcd 为一
 * 表示两个数互质，这样我们就可以把式子和 φ 函数联系起来了。
 * */
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using std::max;
using std::min;
using std::sqrt;

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

struct IM {} getInt;

template<class T> IM& operator>>(IM& im, T &a) {
    a = 0; char c = getchar(); bool n = false;
    for(;!isdigit(c); c = getchar()) if(c == '-') n = true;
    for(; isdigit(c); c = getchar()) a = a * 10 + (c & 15);
    if(n) a = -a;
    return im;
}

long long n;

long long phi(long long x) {
    long long res = x;
    for(long long i = 2; i * i <= x; ++i) if(x % i == 0) {
        res = res / i * (i - 1);
        while(x % i == 0) x /= i;
    }
    if(x > 1) res = res / x * (x - 1);
    return res;
}

int main() {
    getInt >> n;

    long long ans = 0;
    long long lim = sqrt(n);

    for(long long i = 1, j; i <= lim; ++i) if(n % i == 0) {
        j = n / i;
        ans += j * phi(i);
        if(j != i) ans += i * phi(j);
    }

    printf("%lld\n", ans);

    return 0;
}
