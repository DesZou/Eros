/*
 *  luogu2221
 *
 *  线段树维护值，分别维护 val, i * val, i * i * val 。
 *  其实也可以只维护 val ，然后询问的时候再算上 i, i * i 。
 *  所以就跑得没有别人快。
 * */
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <cstring>

const size_t Size = 1e5 + 5;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
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

int n, m;

template<class T> T merge(const T &a, const T &b) {
    return (T){a.val + b.val};
}

template<class T> T gcd(T a, T b) {
    return b? gcd(b, a % b) : a;
}

struct Tag1 {
    long long val;

    void add(long long key, long long l, long long r) {
        val += (r - l + 1) * key;
    }
};

struct Tag2 {
    long long val;

    void add(long long key, long long l, long long r) {
        val += (((l + r) * (r - l + 1)) >> 1) * key;
    }
};

struct Tag3 {
    long long val;

    void add(long long key, long long l, long long r) {
        long long a = r * (r + 1) * ((r << 1) + 1) / 6;
        long long b = (l - 1) * (l) * (((l - 1) << 1) + 1) / 6;
        val += (a - b) * key;
    }
};

template<class T> struct SegmentTree {
    T c[Size << 2];
    long long d[Size << 2];

    void pushup(int i) {
        c[i] = merge(c[i << 1], c[i << 1 | 1]);
    }

    void pushdown(int i, int l, int r) {
        if(d[i] != 0) {
            int mid = (l + r) >> 1;
            c[i << 1].add(d[i], l, mid);
            c[i << 1|1].add(d[i], mid + 1, r);
            d[i << 1] += d[i];
            d[i << 1|1] += d[i];
            d[i] = 0;
        }
    }

    void update(int i, int l, int r, int s, int t, long long key) {
        if(l >= s && r <= t) {
            c[i].add(key, l, r);
            d[i] += key;
        } else {
            int mid = (l + r) >> 1;
            pushdown(i, l, r);
            if(s <= mid) update(i << 1, l, mid, s, t, key);
            if(t > mid) update(i << 1|1, mid + 1, r, s, t, key);
            pushup(i);
        }
    }

    T query(int i, int l, int r, int s, int t) {
        if(l >= s && r <= t) {
            return c[i];
        } else {
            int mid = (l + r) >> 1;
            pushdown(i, l, r);
            if(s > mid) return query(i << 1|1, mid + 1, r, s, t);
            else if(t <= mid) return query(i << 1, l, mid, s, t);
            else return merge(
                    query(i << 1, l, mid, s, mid),
                    query(i << 1|1, mid + 1, r, mid + 1, t));
        }
    }
};

SegmentTree<Tag1> T1;
SegmentTree<Tag2> T2;
SegmentTree<Tag3> T3;

int main() {
    n = input<int>(), m = input<int>();

    for(int i = 1; i <= m; ++i) {
        static char tmp;
        static long long x, y, z, v, l, r;
        do {tmp = std::getchar();} while(tmp != 'C' && tmp != 'Q');
        l = input<long long>(), r = input<long long>();
        if(tmp == 'C') {
            v = input<long long>();
            T1.update(1, 1, n, l, r - 1, v);
            T2.update(1, 1, n, l, r - 1, v);
            T3.update(1, 1, n, l, r - 1, v);
        } else {
            x = + T1.query(1, 1, n, l, r - 1).val * (r - l - l * (r - 1))
                + T2.query(1, 1, n, l, r - 1).val * (l + r - 1)
                - T3.query(1, 1, n, l, r - 1).val;
            z = ((r - l) * (r - l + 1)) >> 1;
            y = gcd(x, z);
            std::printf("%lld/%lld\n", x / y, z / y);
        }
    }

    return 0;
}
