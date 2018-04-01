/*
 *  loj2055
 *
 *  01 排序，二分答案，把小于等于二分值的位置设为 0 ，否则为 0 。
 *  这样区间排序就可以 log n 用线段树维护了，最后看询问点的值。
 *  如果是一，说明当前的二分值小了。时间复杂度 O(m log^2 n) 。
 *  很有用的思想。
 * */
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;

template<class T>
bool chkmin(T &a, const T &b) { return a > b? a = b, 1 : 0; }

template<class T>
bool chkmax(T &a, const T &b) { return a < b? a = b, 1 : 0; }

const char El = 10;
const int Size = 1e5 + 5;

struct SegmentTree {
    int c[Size << 2];
    bool tag[Size << 2];

    void pushup(const int i) { c[i] = c[i << 1] + c[i << 1 | 1]; }

    void pushdown(const int i, int l, int r) {
        if (tag[i]) {
            int key = (c[i] > 0)? 1 : ((c[i] < 0)? -1 : 0);
            int mid = (l + r) >> 1;
            c[i << 1] = key * (mid - l + 1);
            c[i << 1 | 1] = key * (r - mid);
            tag[i << 1] = tag[i << 1 | 1] = true;
            tag[i] = false;
        }
    }

    void update(const int i, int l, int r, int s, int t, int key) {
        if (l >= s && r <= t) {
            c[i] = key * (r - l + 1);
            tag[i] = true;
        } else {
            int mid = (l + r) >> 1;
            pushdown(i, l, r);
            if (s <= mid) update(i << 1, l, mid, s, t, key);
            if (t > mid) update(i << 1 | 1, mid + 1, r, s, t, key);
            pushup(i);
        }
    }

    int query(const int i, int l, int r, int s, int t) {
        if (l >= s && r <= t) return c[i];
        int mid = (l + r) >> 1;
        pushdown(i, l, r);
        return t <= mid
            ? query(i << 1, l, mid, s, t)
            : s > mid
            ? query(i << 1 | 1, mid + 1, r, s, t)
            : query(i << 1, l, mid, s, mid)
            + query(i << 1 | 1, mid + 1, r, mid + 1, t);
    }
} tr;

int n, m, q;
int val[Size];

struct Data { int op, l, r; } d[Size];

int check(const int key, const int pos) {
    for (int i = 1; i <= n; ++i) {
        tr.update(1, 1, n, i, i, (val[i] > key));
    }
    for (Data *i = d + 1; i <= d + m; ++i) {
        int tmp = tr.query(1, 1, n, i->l, i->r);
        if (i->op == 0) {
            tr.update(1, 1, n, i->l, i->r - tmp, 0);
            if (tmp) tr.update(1, 1, n, i->r - tmp + 1, i->r, 1);
        } else {
            tr.update(1, 1, n, i->l + tmp, i->r, 0);
            if (tmp) tr.update(1, 1, n, i->l, i->l + tmp - 1, 1);
        }
    }
    return tr.query(1, 1, n, pos, pos);
}

int binarysearch(int l, int r, const int key) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid, key)) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    cin.sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) cin >> val[i];
    for (int i = 1; i <= m; ++i) cin >> d[i].op >> d[i].l >> d[i].r;

    cin >> q;

    cout << binarysearch(1, n, q) << El;
    
    return 0;
}
