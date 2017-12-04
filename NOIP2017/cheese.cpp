#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>

#define pow(x) ((x) * (x))

const size_t Size = 1e3 + 5;
const double Eps = 1e-8;

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

struct Data {double x, y, z;} d[Size];

int n, h, r, lowbound, upbound;

bool vis[Size];

double dis(int a, int b) {
    if(a == lowbound) {
        if(b == upbound) return h;
        else return d[b].z - r;
    } else if(a == upbound) {
        if(b == lowbound) return h;
        else return h - d[b].z - r;
    } else if(b == lowbound) {
        return d[a].z - r;
    } else if(b == upbound) {
        return h - d[a].z - r;
    } else {
        return std::sqrt(pow(d[a].x - d[b].x) +
                         pow(d[a].y - d[b].y) +
                         pow(d[a].z - d[b].z)) - (r << 1);
    }
}

bool connect() {
    static int q[Size], front, back;
    q[front = 0] = lowbound, back = 1;
    while(front < back) {
        int now = q[front++];
        for(int i = 1; i <= n; ++i)
            if(!vis[i] && dis(i, now) <= Eps)
                vis[i] = true, q[back++] = i;
        if(vis[upbound]) return true;
    } return false;
}

int main() {
    // freopen("cheese.in", "r", stdin);
    // freopen("cheese.out", "w", stdout);

    for(int T = input<int>(); T --> 0;) {
        std::memset(vis, 0, sizeof vis);
        n = input<int>(), h = input<int>(), r = input<int>();
        for(int i = 1, a, b, c; i <= n; ++i) {
            a = input<int>(), b = input<int>(), c = input<int>();
            d[i] = (Data){a, b, c};
        }
        lowbound = ++n, upbound = ++n;
        puts(connect()? "Yes" : "No");
    }

    return 0;
}
