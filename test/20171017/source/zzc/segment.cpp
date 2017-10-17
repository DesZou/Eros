#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <climits>

// const int Inf = -1u >> 1;
const size_t Size = 1e5 + 5;

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

struct Data {long long c, l, r, x;} d[Size];


bool operator<(const Data &a, const Data &b) {
    return a.c > b.c;
}

int n, m, q;

long long a[Size];
long long sum[Size];
long double ans[Size];

struct interval_tree {
    long long c[Size << 2];
    long long tag[Size << 2];

    void pull(int i) {
        c[i] = c[i << 1] + c[i << 1|1];
    }

    void push(int i, int llen, int rlen) {
        if(tag[i]) {
            tag[i << 1] += tag[i];
            tag[i << 1|1] += tag[i];
            c[i << 1] += tag[i] * llen;
            c[i << 1|1] += tag[i] * rlen;
            tag[i] = 0;
        }
    }

    void update(int i, int l, int r, int s, int t, long long key) {
        if(l >= s && r <= t) {
            c[i] += key * (r - l + 1);
            tag[i] += key;
        } else {
            int mid = (l + r) >> 1;
            push(i, mid - l + 1, r - mid);
            if(s <= mid) update(i << 1, l, mid, s, t, key);
            if(t > mid) update(i << 1|1, mid + 1, r, s, t, key);
            pull(i);
        }
    }

    long long query(int i, int l, int r, int s, int t) {
        if(l >= s && r <= t) {
            return c[i];
        } else {
            int mid = (l + r) >> 1;
            push(i, mid - l + 1, r - mid);
            if(t <= mid) return query(i << 1, l, mid, s, t);
            else if(s > mid) return query(i << 1|1, mid + 1, r, s, t);
            else return query(i << 1, l, mid, s, mid)
                      + query(i << 1|1, mid + 1, r, mid + 1, t);
        }
    }
} T, F, G;

int main() {
    freopen("segment.in", "r", stdin);
    freopen("segment.out", "w", stdout);

    n = input<int>(), m = input<int>(), q = input<int>();

    for(int i = 1; i <= n; ++i) a[i] = input<long long>();

    for(int i = 1; i <= m; ++i) {
        d[i].c = input<long long>(), d[i].l = input<long long>();
        d[i].r = input<long long>(), d[i].x = input<long long>();
    }

    std::sort(d + 1, d + 1 + m);

    int ptr = 1;

    for(; ptr <= m && d[ptr].c == 2; ++ptr)
        F.update(1, 1, n, d[ptr].l, d[ptr].r, d[ptr].x),
        T.update(1, 1, n, d[ptr].l, d[ptr].r, 1);

    for(int i = 1; i <= n; ++i) {
        static long long x, y;
        x = F.query(1, 1, n, i, i);
        sum[i] = y = T.query(1, 1, n, i, i);
        ans[i] = x? (long double)x / y : a[i];
    }

    for(; ptr <= m; ++ptr)
        G.update(1, 1, n, d[ptr].l, d[ptr].r, d[ptr].x);

    for(int i = 1; i <= n; ++i) {
        ans[i] += ans[i - 1] + (long double)G.query(1, 1, n, i, i) / (sum[i] + 1);
    }

    for(int i = 0, l, r; i < q; ++i) {
        l = input<int>(), r = input<int>();
        printf("%.3Lf\n", ans[r] - ans[l - 1]);
    }

    return 0;
}
