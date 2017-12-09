/*
Name: LuoGu P2605
Time: 2017.11.3
Status: Accepted
Author: Dez
考虑朴素的转移方程，设f[i][j]为最后设立基站的点是i，总共设了j个基站，
满足1~i的村庄的要求所需的最少费用。
转移方程为：f[i][j] = min(k<i){f[k][j-1] + cost(k, i)} + c[i]。
其中c[i]与题中同义。cost(i, k)为i与k均设基站但是中间没有其它基站所需要支付的补偿费用。
发现只要能快速求出cost()函数，就能加速转移。
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>

#define left i << 1, l, mid
#define right i << 1|1, mid + 1, r
#define init 1, 1, n

const int Inf = -1u >> 1;
const int Size = 2e4 + 5;

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

typedef int array[Size];

struct segment_tree {
    int elem[Size << 2];
    int tag[Size << 2];

    void pull(int i) {
        elem[i] = min(elem[i << 1], elem[i << 1|1]);
    }

    void push(int i) {
        if(tag[i]) {
            elem[i << 1] += tag[i];
            elem[i << 1|1] += tag[i];
            tag[i << 1] += tag[i];
            tag[i << 1|1] += tag[i];
            tag[i] = 0;
        }
    }

    void build(int i, int l, int r, int *key) {
        if(l == r) {
            elem[i] = key[l];
        } else {
            int mid = (l + r) >> 1; tag[i] = 0;
            build(left, key), build(right, key);
            pull(i);
        }
    }

    void update(int i, int l, int r, int s, int t, int key) {
        if(l >= s && r <= t) {
            tag[i] += key, elem[i] += key;
        } else {
            int mid = (l + r) >> 1; 
            push(i);
            if(s <= mid) update(left, s, t, key);
            if(t > mid) update(right, s, t, key);
            pull(i);
        }
    }

    int query(int i, int l, int r, int s, int t) {
        if(l >= s && r <= t) {
            return elem[i];
        } else {
            int mid = (l + r) >> 1;
            push(i);
            if(t <= mid) return query(left, s, t);
            else if(s > mid) return query(right, s, t);
            else return min(query(left, s, mid), query(right, mid + 1, t));
        }
    }
} T;

int n, k, ans;

array f, d, c, w, s, l, r;

std::vector<int> end[Size];

int dist(int x, int y) {
    return d[x] - d[y];
}

template<bool CMP> bool cmp(int x, int y) {}

int main() {
    n = input<int>() + 1, k = input<int>() + 1; // to add an end point

    d[n] = Inf, c[n] = 0, w[n] = Inf; // the endpoint's properties

    for(int i = 2; i < n; ++i) d[i] = input<int>();
    for(int i = 1; i < n; ++i) c[i] = input<int>();
    for(int i = 1; i < n; ++i) s[i] = input<int>();
    for(int i = 1; i < n; ++i) w[i] = input<int>();

    for(int i = 1; i <= n; ++i)
        r[i] = std::upper_bound(d + 1, d + 1 + n, d[i] + s[i]) - d - 1,
        end[r[i]].push_back(i);
    for(int i = 1; i <= n; ++i)
        l[i] = std::lower_bound(d + 1, d + 1 + n, d[i] - s[i]) - d;

    for(int i = 1, tmp = 0; i <= n; ++i) {
        f[i] = tmp + c[i];
        for(int j = end[i].size() - 1; j >= 0; --j)
            tmp += w[end[i][j]];
    }

    ans = f[n];

    for(int h = 2; h <= k; ++h) {
        T.build(init, f);
        for(int i = 1; i <= n; ++i) {
            f[i] = c[i] + ((i > 1)? T.query(init, 1, i - 1) : 0);
            for(int j = end[i].size() - 1; j >= 0; --j)
                if(l[end[i][j]] > 1) T.update(init, 1, l[end[i][j]] - 1, w[end[i][j]]);
        } chkmin(ans, f[n]);
    }

    printf("%d\n", ans);

    return 0;
}
