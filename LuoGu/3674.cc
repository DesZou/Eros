/*
 *  luogu3674
 *
 *  莫队。
 *  分块没什么特别之处，但是维护值用到了 bitset 。
 *  注意两数之和等于 x 的情况，存一个负数的 bitset 用来判断 a = -b - (-x) 。
 *  乘法就枚举约数暴力判断。
 *  时间复杂度 O(m√(c)) or O(mc/64) 。（搞不清到底有多慢）
 * */
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>

const size_t Size = 1e5 + 5;
const int REV = Size;

int n, m, sp;

int a[Size];

int cnt[Size];

bool ans[Size];

std::bitset<Size> s, rs;

struct Data {
    int l, r, opt, id, inv, x;
} d[Size];

bool operator<(const Data &a, const Data &b) {
    return a.inv == b.inv? a.r < b.r : a.inv < b.inv;
}

inline void add(int p) {
    static int x; x = a[p];
    if(++cnt[x] == 1) s[x] = rs[REV - x] = 1;
}

inline void quit(int p) {
    static int x; x = a[p];
    if(--cnt[x] == 0) s[x] = rs[REV - x] = 0;
}

int main() {
    std::scanf("%d%d", &n, &m);

    sp = std::sqrt(n);

    for(int i = 1; i <= n; ++i)
        std::scanf("%d", a + i);

    for(int i = 1; i <= m; ++i) {
        std::scanf("%d%d%d%d", &d[i].opt, &d[i].l, &d[i].r, &d[i].x);
        d[i].id = i;
        d[i].inv = d[i].l / sp;
    }

    std::sort(d + 1, d + 1 + m);

    for(int i = 1, l = 1, r = 0; i <= m; ++i) {
        while(r < d[i].r) add(++r);
        while(r > d[i].r) quit(r--);
        while(l < d[i].l) quit(l++);
        while(l > d[i].l) add(--l);
        if(d[i].opt == 1) {
            if((s & (s << d[i].x)).any()) ans[d[i].id] = true;
        } else if(d[i].opt == 2) {
            if((s & (rs >> (REV - d[i].x))).any()) ans[d[i].id] = true;
        } else {
            for(int j = 1; j * j <= d[i].x; ++j) if(d[i].x % j == 0)
                if(s[j] && s[d[i].x / j]) {ans[d[i].id] = true; break;}
        }
    }

    for(int i = 1; i <= m; ++i)
        std::puts(ans[i]? "hana" : "bi");

    return 0;
}
