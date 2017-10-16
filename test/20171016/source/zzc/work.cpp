#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

#define init 1, 1, (n << 1)

const size_t Size = 3e5 + 5;
const int Inf = 0x3f3f3f3f;

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

struct interval_tree {
    int c[Size << 1 << 2];
    int first[Size << 1 << 2];
    int last[Size << 1 << 2];

    interval_tree() {std::memset(first, 0x3f, sizeof first);}

    inline void pull(int i) {
        c[i] = c[i << 1] + c[i << 1|1];
        first[i] = min(first[i << 1], first[i << 1|1]);
        last[i] = max(last[i << 1], last[i << 1|1]);
    }

    void update(int i, int l, int r, int pos, int key) {
        if(l == r) {
            c[i] += key;
            first[i] = c[i]? l : Inf;
            last[i] = c[i]? r : 0;
        } else {
            int mid = (l + r) >> 1;
            if(pos <= mid) update(i << 1, l, mid, pos, key);
            else     update(i << 1|1, mid + 1, r, pos, key);
            pull(i);
        }
    }

    int yank(int i, int l, int r, int s, int t) {
        if(l >= s && r <= t) {
            return first[i];
        } else {
            int mid = (l + r) >> 1;
            if(s <= mid && last[i << 1] >= s)
                return yank(i << 1, l, mid, s, t);
            else if(t > mid && first[i << 1|1] <= t)
                return yank(i << 1|1, mid + 1, r, s, t);
            else return -1;
        }
    }
} T;

struct Data {int s, t;} d[Size];

int n, m;

int dex[Size << 1], lim;

bool operator<(const Data &a, const Data &b) {
    return a.s < b.s;
}

int main() {
    freopen("work.in", "r", stdin);
    freopen("work.out", "w", stdout);

    n = input<int>(), m = input<int>();

    for(int i = 1; i <= n; ++i) {
        d[i].s = input<int>(), d[i].t = input<int>();
        d[i].t += d[i].s;
        dex[++lim] = d[i].s, dex[++lim] = d[i].t;
    }

    std::sort(d + 1, d + 1 + n);
    std::sort(dex + 1, dex + 1 + lim);
    lim = std::unique(dex + 1, dex + 1 + lim) - dex;

    int ans = 0;

    for(int i = 1, x, y, z, u; i <= n; ++i) {
        x = std::lower_bound(dex + 1, dex + lim, d[i].s) - dex;
        y = std::lower_bound(dex + 1, dex + lim, d[i].t) - dex;
        u = std::lower_bound(dex + 1, dex + lim, d[i].s - m) - dex;
        if(dex[u] < d[i].s - m) ++u;
        z = T.yank(init, u, x);
        if(z > 0) ++ans, T.update(init, z, -1);
        T.update(init, y, 1);
    }

    printf("%d\n", ans);

    return 0;
}
