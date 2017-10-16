#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

// const int Inf = 0x3f3f3f3f;
const size_t Size = 2e5 + 5;

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

struct Query {int l, r, id;} d[Size];

bool operator<(const Query &a, const Query &b) {
    return a.r < b.r;
}

int n, m, k;

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

    void update(int i, int l, int r, int s, int t, int key) {
        if(l >= s && r <= t) {
            c[i] += (r - l + 1) * key;
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
} T;

int a[Size];
int s[Size];
long long ans[Size];

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);

    n = input<int>(), m = input<int>(), k = input<int>();

    for(int i = 1; i <= n; ++i) {
        a[i] = input<int>();
        s[i] = s[i - 1] + (a[i] >= m);
    }

    int q = input<int>();

    for(int i = 1; i <= q; ++i) {
        d[i].l = input<int>(), d[i].r = input<int>();
        d[i].id = i;
    }

    std::sort(d + 1, d + 1 + q);

    for(int i = 1, l = 0, x = 1; i <= n; ++i) {
        while(s[i] - s[l] >= k && l < n) ++l;
        if(l) T.update(1, 1, n, 1, l, 1);
        while(x <= q && d[x].r == i) {
            ans[d[x].id] = T.query(1, 1, n, d[x].l, d[x].r);
            ++x;
        }
    }

    for(int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);

    return 0;
}
