#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cctype>

const size_t Size = 2e5 + 5;
const size_t Log = 18; // 17.6096

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(std::getchar()); bool n(false);
    for(; !std::isdigit(c); c = std::getchar()) if(c == '-') n = 1;
    for(; std::isdigit(c); c = std::getchar()) r = r * 10 - 48 + c;
    return n? -r : r;
}

int n, m, lim;

int root[Size];
int val[Size];
int dVal[Size];

struct Node {
    int val;
    int ch[2];
} c[(Size << 2) * Log];

int _Index;

void build(int &rt, int l, int r) {
    c[rt = ++_Index].val = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        build(c[rt].ch[0], l, mid);
        build(c[rt].ch[1], mid + 1, r);
    }
}

void update(int &rt, int l, int r, int pos, int key) {
    c[++_Index] = c[rt];
    c[rt = _Index].val += key;
    if(l != r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) update(c[rt].ch[0], l, mid, pos, key);
        else update(c[rt].ch[1], mid + 1, r, pos, key);
    }
}

int query(const int &fst, const int &lst, int l, int r, int rnk) {
    if(l == r) return l;
    int tmp = c[c[lst].ch[0]].val - c[c[fst].ch[0]].val;
    int mid = (l + r) >> 1;
    return rnk > tmp
        ? query(c[fst].ch[1], c[lst].ch[1], mid + 1, r, rnk - tmp)
        : query(c[fst].ch[0], c[lst].ch[0], l, mid, rnk);
}

int main() {
    n = input<int>(), m = input<int>();

    for(int i = 1; i <= n; ++i)
        dVal[i] = val[i] = input<int>();

    std::sort(dVal + 1, dVal + 1 + n);
    lim = std::unique(dVal + 1, dVal + 1 + n) - dVal - 1;

    // build(root[0], 1, lim);

    for(int i = 1, t; i <= n; ++i) {
        t = std::lower_bound(dVal + 1, dVal + 1 + lim, val[i]) - dVal;
        update(root[i] = root[i - 1], 1, lim, t, 1);
    }

    for(int l, r, k; m --> 0;) {
        l = input<int>(), r = input<int>(), k = input<int>();
        std::printf("%d\n", dVal[query(root[l - 1], root[r], 1, lim, k)]);
    }

    return 0;
}
