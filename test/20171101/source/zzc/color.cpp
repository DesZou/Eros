#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

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
    T r(0); char c(getchar()); bool n(false);
    while(c > '9' || c < '0') {if(c == '-') n = true; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

struct Change {
    int p, c;
} chg[Size];

struct Query {
    int l, r, id, time, inv;
} qry[Size];

bool operator<(const Query &a, const Query &b) {
    if(a.inv != b.inv) return a.inv < b.inv;
    else if(a.r / 3500 != b.r / 3500) return a.r < b.r;
    else return a.time < b.time;
}

int L, R, T;

long long S;

int n, m, chgnum, base, qrynum;

int c[Size], num[Size];

long long w[Size];

long long ans[Size];

void change(int x) {
    std::swap(c[chg[x].p], chg[x].c);
    if(chg[x].p > L && chg[x].p <= R) {
        if(!num[c[chg[x].p]]) S += w[c[chg[x].p]];
        ++num[c[chg[x].p]];
        --num[chg[x].c];
        if(!num[chg[x].c]) S -= w[chg[x].c];
    }
}

void add(int x) {
    if(!num[c[x]]) S += w[c[x]];
    ++num[c[x]];
}

void remove(int x) {
    --num[c[x]];
    if(!num[c[x]]) S -= w[c[x]];
}

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);

    n = input<int>(), m = input<int>();

    base = std::pow(n, 1.666);

    for(int i = 1; i <= n; ++i) c[i] = input<int>();
    for(int i = 1; i <= n; ++i) w[i] = input<long long>();

    for(int i = 1, l, r, kind; i <= m; ++i) {
        kind = input<int>();
        l = input<int>(), r = input<int>();
        if(kind == 1) {
            chg[++chgnum] = (Change){l, r};
        } else {
            ++qrynum;
            qry[qrynum] = (Query){l, r, qrynum, chgnum, l / 3500};
        }
    }

    std::sort(qry + 1, qry + 1 + qrynum);

    for(int i = 1; i <= qrynum; ++i) {
        while(qry[i].time > T) change(++T);
        while(qry[i].time < T) change(T--);
        while(qry[i].r > R) add(++R);
        while(qry[i].r < R) remove(R--);
        while(qry[i].l > L + 1) remove(++L);
        while(qry[i].l < L + 1) add(L--);
        ans[qry[i].id] = S;
    }

    for(int i = 1; i <= qrynum; ++i)
        printf("%lld\n", ans[i]);

    return 0;
}
