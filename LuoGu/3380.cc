/*
 * luogu3380
 *
 * 标解应该有平衡树，用带修改主席树实现查前驱后继就怪怪的。
 * 但是主席树够强啊，跑得还特别快。（比较快）
 * */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <limits>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;

template<class T>
bool chkmin(T &a, const T &b) { return a > b? a = b, 1 : 0; }

template<class T>
bool chkmax(T &a, const T &b) { return a < b? a = b, 1 : 0; }

const char El = 10;
const int Size = 5e4 + 5;
const int Log = 17;
const int Inf = std::numeric_limits<int>::max();

struct Node { int ch[2], val; } c[Size * Log * Log * 2];
struct Data { int opt, l, r, k, pos; } d[Size];

struct Hash {
    int elem[Size * 2], len;

    void init() {
        std::sort(elem + 1, elem + 1 + len);
        len = std::unique(elem + 1, elem + 1 + len) - elem - 1;
    }

    void push(const int x) { elem[++len] = x; }

    int operator[](const int x) {
        return std::lower_bound(elem + 1, elem + 1 + len, x) - elem;
    }
} hash;

int _Index;
int n, m;
int root[Size * 2];

void update(int &i, int l, int r, int pos, int key) {
    if (!i) i = ++_Index;
    c[i].val += key;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(c[i].ch[0], l, mid, pos, key);
    else update(c[i].ch[1], mid + 1, r, pos, key);
}

inline int lowbit(const int x) { return -x & x; }

void modify(int p, int pos, int key) {
    for (; p <= n; p += lowbit(p)) update(root[p], 1, hash.len, pos, key);
}

int tmpf[Log * 2], tmpl[Log * 2];

void load(const int &fst, const int &lst) {
    *tmpf = *tmpl = 0;
    for (int i = fst; i; i -= lowbit(i)) tmpf[++(*tmpf)] = root[i];
    for (int i = lst; i; i -= lowbit(i)) tmpl[++(*tmpl)] = root[i];
}

void move(const bool dir) {
    for (int i = 1; i <= *tmpf; ++i) tmpf[i] = c[tmpf[i]].ch[dir];
    for (int i = 1; i <= *tmpl; ++i) tmpl[i] = c[tmpl[i]].ch[dir];
}

int kth(int l, int r, int rank) {
    if (l == r) return hash.elem[l];
    int sum = 0, mid = (l + r) >> 1;
    for (int i = 1; i <= *tmpf; ++i) sum -= c[c[tmpf[i]].ch[0]].val;
    for (int i = 1; i <= *tmpl; ++i) sum += c[c[tmpl[i]].ch[0]].val;
    move(sum < rank);
    return sum < rank
        ? kth(mid + 1, r, rank - sum)
        : kth(l, mid, rank);
} 

int rank(int l, int r, int var, bool showMore = false) {
    if (l == r) {
        if (!showMore) return 1;
        int res = 0;
        for (int i = 1; i <= *tmpf; ++i) res -= c[tmpf[i]].val;
        for (int i = 1; i <= *tmpl; ++i) res += c[tmpl[i]].val;
        return res;
    } else {
        int mid = (l + r) >> 1;
        if (var > mid) {
            int sum = 0;
            for (int i = 1; i <= *tmpf; ++i) sum -= c[c[tmpf[i]].ch[0]].val;
            for (int i = 1; i <= *tmpl; ++i) sum += c[c[tmpl[i]].ch[0]].val;
            move(1);
            return sum + rank(mid + 1, r, var, showMore);
        } else {
            move(0);
            return rank(l, mid, var, showMore);
        }
    }
}

int w[Size];

int main() {
    cin.sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        hash.push(w[i]);
    }

    for (int i = 1; i <= m; ++i) {
        cin >> d[i].opt;
        if (d[i].opt == 3) {
            cin >> d[i].pos >> d[i].k;
        } else {
            cin >> d[i].l >> d[i].r >> d[i].k;
        }
        if (d[i].opt != 2) hash.push(d[i].k);
    }

    hash.init();
    
    for (int i = 1; i <= n; ++i) modify(i, hash[w[i]], 1);

    for (int i = 1, x; i <= m; ++i)
        switch (d[i].opt) {
            case 1:
                load(d[i].l - 1, d[i].r);
                cout << rank(1, hash.len, hash[d[i].k]) << El;
                break;
            case 2:
                load(d[i].l - 1, d[i].r);
                cout << kth(1, hash.len, d[i].k) << El;
                break;
            case 3:
                modify(d[i].pos, hash[w[d[i].pos]], -1);
                modify(d[i].pos, hash[w[d[i].pos] = d[i].k], 1);
                break;
            case 4:
                load(d[i].l - 1, d[i].r);
                x = rank(1, hash.len, hash[d[i].k]);
                if (x == 1) {
                    cout << -Inf << El;
                } else {
                    load(d[i].l - 1, d[i].r);
                    cout << kth(1, hash.len, x - 1) << El;
                }
                break;
            case 5:
                load(d[i].l - 1, d[i].r);
                x = rank(1, hash.len, hash[d[i].k], true);
                if (x == d[i].r - d[i].l + 1) {
                    cout << Inf << El;
                } else {
                    load(d[i].l - 1, d[i].r);
                    cout << kth(1, hash.len, x + 1) << El;
                }
                break;
            default:
                return -1;
        }

    return 0;
}
