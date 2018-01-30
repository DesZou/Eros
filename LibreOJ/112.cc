/*
 *  libreoj112
 *
 *  CDQ 分治，第一维直接排序，第二维用归并处理，
 *  第三维用树状数组维护。要注意的是因为是偏序关系，
 *  而分治的时候不好判断相等的情况，所以最后统计答案
 *  应该以相同三元组的最大答案为准。
 * */
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iostream>

const size_t Size = 1e5 + 5;
const size_t Scale = 2e5 + 5;

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
    while(!std::isdigit(c)) {if(c == '-') n = 1; c = std::getchar();}
    while(std::isdigit(c)) {r = r * 10 - 48 + c, c = std::getchar();}
    return n? -r : r;
}

int n, k;

int ans[Scale];

struct Data {
    int x, y, z, f;
} a[Size], t[Size];

bool operator<(const Data &a, const Data &b) {
    return a.x == b.x? a.y == b.y? a.z < b.z : a.y < b.y : a.x < b.x;
}

bool operator==(const Data &a, const Data &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator!=(const Data &a, const Data &b) {
    return !(a == b);
}

struct BinaryIndexedTree {
    int c[Scale];

    inline int lowbit(int x) {
        return -x & x;
    }

    void modify(int x, int key) {
        for(; x <= k; x += lowbit(x)) c[x] += key;
    }

    int sum(int x, int res = 0) {
        for(; x > 0; x -= lowbit(x)) res += c[x];
        return res;
    }
} T;

void cdqPartition(int l, int r) {
    if(l == r) return;
    int mid = (l + r) >> 1;
    cdqPartition(l, mid), cdqPartition(mid + 1, r);

    int cnt = l, j = l;

    for(int i = mid + 1; i <= r; ++i) {
        for(; j <= mid && a[j].y <= a[i].y; ++j)
            T.modify((t[cnt++] = a[j]).z, 1);
        (t[cnt++] = a[i]).f += T.sum(a[i].z);
    }

    for(; j <= mid; ++j) T.modify((t[cnt++] = a[j]).z, 1);

    for(int i = l; i <= mid; ++i) T.modify(a[i].z, -1);
    for(int i = l; i <= r; ++i) a[i] = t[i];
}

int main() {
    n = input<int>(), k = input<int>();

    for(int i = 1; i <= n; ++i) {
        a[i].x = input<int>();
        a[i].y = input<int>();
        a[i].z = input<int>();
    }

    std::sort(a + 1, a + 1 + n);

    cdqPartition(1, n);

    std::sort(a + 1, a + 1 + n);

    for(int i = 1, t = 0, k = 0; i <= n; ++i) {
        chkmax(t, a[i].f), ++k;
        if(a[i] != a[i + 1]) ans[t] += k, k = t = 0;
    }

    for(int i = 0; i < n; ++i)
        std::printf("%d\n", ans[i]);

    return 0;
}
