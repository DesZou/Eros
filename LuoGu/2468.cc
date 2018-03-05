/*
 * luogu2468
 *
 * 一道二合一题，有多行时用二维前缀和二分，
 * 二分的值是选取的数的范围 z ，题目只要求选的数的数量最小，
 * 所以肯定从大的开始选。用数组 num[x][y][z] 表示在第 1..x 行，
 * 第 1..y 列中间， >= z 的数字有多少个， sum[x][y][z] 表示
 * 满足上列条件的数字之和，这样就可以二分了。
 * 只有一行的时候用主席树就好了，比前面暴力还好写。
 * 注意除法上的技巧。
 * */
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using std::max;
using std::min;
using std::cerr;
using std::endl;

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

struct IM {} getInt;

template<class T> IM& operator>>(IM& im, T &a) {
    a = 0; char c = getchar(); bool n = false;
    for (;!isdigit(c); c = getchar()) if (c == '-') n = true;
    for (; isdigit(c); c = getchar()) a = a * 10 + (c & 0xf);
    if(n) a = -a; return im;
}

const int Size = 5e5 + 5;
const int Log = 20;
const int Lim = 1000;

struct Node {
    int num, sum, ch[2];
} c[Size * Log];

int _Index;

int root[Size];

void update(int &i, int l, int r, int pos, int key) {
    c[++_Index] = c[i];
    c[i = _Index].num += key;
    c[i].sum += pos * key;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(c[i].ch[0], l, mid, pos, key);
    else update(c[i].ch[1], mid + 1, r, pos, key);
}

int query(const int &fst, const int &lst, int l, int r, int key) {
    if (l == r) {
        return (key + l - 1) / l;
    } else {
        int mid = (l + r) >> 1;
        int tmp = c[c[lst].ch[1]].sum - c[c[fst].ch[1]].sum;
        return (tmp >= key)
            ? query(c[fst].ch[1], c[lst].ch[1], mid + 1, r, key)
            : query(c[fst].ch[0], c[lst].ch[0], l, mid, key - tmp)
            + c[c[lst].ch[1]].num - c[c[fst].ch[1]].num;
    }
}

int line, col, m;

namespace BruteForce {
    const int Size2 = 200 + 5;
    int p[Size2][Size2];
    int lim;
    int sum[Size2][Size2][Lim + 5];
    int num[Size2][Size2][Lim + 5]; // XXX Lim is not std::size_t !!

    int fig(int x1, int y1, int x2, int y2, int key) {
        return sum[x2][y2][key]
                - sum[x2][y1 - 1][key]
                - sum[x1 - 1][y2][key]
                + sum[x1 - 1][y1 - 1][key];
    }

    int cnt(int x1, int y1, int x2, int y2, int key) {
        return num[x2][y2][key]
                - num[x2][y1 - 1][key]
                - num[x1 - 1][y2][key]
                + num[x1 - 1][y1 - 1][key];
    }

    int binarySearch(int x1, int y1, int x2, int y2, int key) {
        if (fig(x1, y1, x2, y2, 0) < key) return -1;
        int l = 0, r = lim + 1, res;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if(fig(x1, y1, x2, y2, mid) >= key) l = res = mid;
            else r = mid;
        }
        return cnt(x1, y1, x2, y2, res) - (fig(x1, y1, x2, y2, res) - key) / res;
    }

    int run() {
        for (int i = 1; i <= line; ++i)
            for (int j = 1; j <= col; ++j) {
                getInt >> p[i][j];
                chkmax(lim, p[i][j]);
            }

        for (int k = 0; k <= lim; ++k)
            for (int i = 1; i <= line; ++i)
                for (int j = 1; j <= col; ++j) {
                    sum[i][j][k] = sum[i - 1][j][k]
                                 + sum[i][j - 1][k]
                                 - sum[i - 1][j - 1][k]
                                 + (p[i][j] >= k? p[i][j] : 0);
                    num[i][j][k] = num[i - 1][j][k]
                                 + num[i][j - 1][k]
                                 - num[i - 1][j - 1][k]
                                 + (p[i][j] >= k);
                }

        for (int i = 1, x1, x2, y1, y2, h, ans; i <= m; ++i) {
            getInt >> x1 >> y1 >> x2 >> y2 >> h;
            ans = binarySearch(x1, y1, x2, y2, h);
            if(ans == -1) puts("Poor QLW");
            else printf("%d\n", ans);
        }

        return 0;
    }
}

int main() {
    getInt >> line >> col >> m;

    if (line != 1) {
        return BruteForce::run();
    }

    for (int a, i = 1; i <= col; ++i) {
        getInt >> a;
        update(root[i] = root[i - 1], 1, Lim, a, 1);
    }

    for (int i = 1, l, r, h; i <= m; ++i) {
        getInt >> l >> l >> r >> r >> h;
        if (c[root[r]].sum - c[root[l - 1]].sum < h) {
            puts("Poor QLW");
        } else {
            printf("%d\n", query(root[l - 1], root[r], 1, Lim, h));
        }
    }

    return 0;
}
