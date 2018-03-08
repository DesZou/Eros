/*
 * luogu2042
 *
 * fhq_treap 实现平衡树，支持区间插入，区间删除，区间修改，区间翻转
 * 区间求和，区间最大子段和。内存很小所以还用了内存池。
 * 各种标记维护得我要吐血了。可以当模板了。
 * */
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stack>

using std::max;
using std::min;
using std::cerr;
using std::endl;
using std::rand;
using std::swap;
using std::stack;

template<class T>
bool chkmin(T &a, const T &b) { return a > b? a = b, 1 : 0; }

template<class T>
bool chkmax(T &a, const T &b) { return a < b? a = b, 1 : 0; }

struct IM {} getInt;

template<class T> IM& operator>>(IM &im, T &a) {
    a = 0; char c = getchar(); bool n = false;
    for (;!isdigit(c); c = getchar()) if (c == '-') n = true;
    for (; isdigit(c); c = getchar()) a = a * 10 + (c & 0xf);
    if (n) a = -a; return im;
}

const int Size = 5e5 + 5;

struct MemPool {
    int _Index;

    int stk[Size], top;

    int getMem() {
        if (top) {
            return stk[--top];
        } else {
            return ++_Index;
        }
    }

    void cycleMem(int x) {
        stk[top++] = x;
    }
} mpool;

struct Node {
    int val, sum, fix, mxsum, lxsum, rxsum, size, ch[2];
    bool rev, asg;
} c[Size];

void pushup(int x) {
    Node &p = c[x];
    p.sum = p.val + c[p.ch[0]].sum + c[p.ch[1]].sum;
    p.size = 1 + c[p.ch[0]].size + c[p.ch[1]].size;
    p.lxsum = max(c[p.ch[0]].lxsum, c[p.ch[0]].sum + p.val + c[p.ch[1]].lxsum);
    p.rxsum = max(c[p.ch[1]].rxsum, c[p.ch[1]].sum + p.val + c[p.ch[0]].rxsum);
    p.mxsum = max(max(c[p.ch[0]].mxsum, c[p.ch[1]].mxsum),
                  c[p.ch[0]].rxsum + p.val + c[p.ch[1]].lxsum);
}

void reverse(int x) {
    c[x].rev ^= 1;
    swap(c[x].ch[0], c[x].ch[1]);
    swap(c[x].lxsum, c[x].rxsum);
}

void assign(int x, int val) {
    c[x].val = val;
    c[x].sum = val * c[x].size;
    c[x].mxsum = max(c[x].val, c[x].sum);
    c[x].rxsum = c[x].lxsum = max(0, c[x].sum);
    c[x].asg = true;
}

void pushdown(int x) {
    if (c[x].rev) {
        c[x].rev = 0;
        if (c[x].ch[0]) reverse(c[x].ch[0]);
        if (c[x].ch[1]) reverse(c[x].ch[1]);
    }
    if (c[x].asg) {
        c[x].asg = 0;
        if (c[x].ch[0]) assign(c[x].ch[0], c[x].val);
        if (c[x].ch[1]) assign(c[x].ch[1], c[x].val);
    }
}

int newNode(int x) {
    int p = mpool.getMem();
    c[p].val = c[p].sum = c[p].mxsum = x;
    c[p].size = 1;
    c[p].fix = rand();
    c[p].lxsum = c[p].rxsum = max(0, x);
    c[p].ch[0] = c[p].ch[1] = 0;
    c[p].rev = c[p].asg = 0;
    return p;
}

int merge(int x, int y) {
    if (!x || !y) {
        return x | y;
    } else if (c[x].fix < c[y].fix) {
        pushdown(x);
        c[x].ch[1] = merge(c[x].ch[1], y);
        pushup(x);
        return x;
    } else {
        pushdown(y);
        c[y].ch[0] = merge(x, c[y].ch[0]);
        pushup(y);
        return y;
    }
}

void split(int z, int key, int &x, int &y) {
    if (!z) {
        x = y = 0;
    } else {
        pushdown(z);
        if (c[c[z].ch[0]].size < key) {
            split(c[z].ch[1], key - c[c[z].ch[0]].size - 1, c[z].ch[1], y);
            x = z;
        } else {
            split(c[z].ch[0], key, x, c[z].ch[0]);
            y = z;
        }
        pushup(z);
    }
}

void remove(int x) {
    if (c[x].ch[0]) remove(c[x].ch[0]);
    mpool.cycleMem(x);
    if (c[x].ch[1]) remove(c[x].ch[1]);
}

void traversal(int x) {
    pushdown(x);
    if (c[x].ch[0]) traversal(c[x].ch[0]);
    cerr << " " << c[x].val;
    if (c[x].ch[1]) traversal(c[x].ch[1]);
    pushup(x);
}

int n, m;

int root;

int stk[Size], top;

int main() {
    c[0].mxsum = -INT_MAX / 2;

    getInt >> n >> m;

    for (int i = 1, x; i <= n; ++i) {
        getInt >> x;
        stk[top] = newNode(x);
        if (top > 0) c[stk[top - 1]].ch[1] = stk[top];
        ++top;
    }

    while (--top >= 0) pushup(stk[top]);

    root = stk[0];

    char cmd[10];
    int u, v, w;
    for (int i = 1, pos, tot, key; i <= m; ++i) {
        scanf("%s", cmd);
        switch (cmd[2]) {
        case 'S': // INSERT
            getInt >> pos >> tot;
            split(root, pos, u, v);
            top = 0;
            for (int j = 1, x; j <= tot; ++j) {
                getInt >> x;
                stk[top] = newNode(x);
                if (top > 0) c[stk[top - 1]].ch[1] = stk[top];
                ++top;
            }
            while (--top >= 0) pushup(stk[top]);
            root = merge(merge(u, stk[0]), v);
            break;
        case 'L': // DELETE
            getInt >> pos >> tot;
            split(root, pos - 1, u, v);
            split(v, tot, v, w);
            root = merge(u, w);
            remove(v);
            break;
        case 'V': // REVERSE
            getInt >> pos >> tot;
            split(root, pos - 1, u, v);
            split(v, tot, v, w);
            reverse(v);
            root = merge(u, merge(v, w));
            break;
        case 'T': // GET-SUM
            getInt >> pos >> tot;
            split(root, pos - 1, u, v);
            split(v, tot, v, w);
            printf("%d\n", c[v].sum);
            root = merge(u, merge(v, w));
            break;
        case 'X': // MAX-SUM
            printf("%d\n", c[root].mxsum);
            break;
        case 'K': // MAKE-SAME
            getInt >> pos >> tot >> key;
            split(root, pos - 1, u, v);
            split(v, tot, v, w);
            assign(v, key);
            root = merge(u, merge(v, w));
            break;
        default:
            return -1;
        }
    }

    return 0;
}
