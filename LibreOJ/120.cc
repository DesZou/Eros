#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

template<class T> T min(const T &a, const T &b)
{ return a < b? a : b; }

template<class T> T max(const T &a, const T &b)
{ return a > b? a : b; }

template<class T> bool chkmin(T &a, const T &b)
{ return a > b? a = b, 1 : 0; }

template<class T> bool chkmax(T &a, const T &b)
{ return a < b? a = b, 1 : 0; }

struct IM { template<class T> IM& operator>>(T&); } getInt;

template<class T> IM& IM::operator>>(T &a) {
    a = 0; char c = getchar(); bool n = false;
    for(;!isdigit(c); c = getchar()) if(c == '-') n = true;
    for(; isdigit(c); c = getchar()) a = a * 10 + (c & 15);
    if(n) a = -a;
    return *this;
}

const size_t Size = 3e5 + 5;
const int Log = 20;

struct Node {
    int val, size, fix, ch[2];
} c[Size * Log];

int root[Size];

int _Index;

void pushup(int x) {
    c[x].size = 1 + c[c[x].ch[0]].size + c[c[x].ch[1]].size;
}

int newNode(int val) {
    c[++_Index].val = val;
    c[_Index].fix = std::rand();
    c[_Index].size = 1;
    return _Index;
}

int copyNode(int x) {
    c[++_Index] = c[x];
    return _Index;
}

int merge(int x, int y) {
    if(!x || !y) {
        return x | y; // copyNode(x | y)
    } else {
        if(c[x].fix < c[y].fix) {
            // x = copyNode(x);
            c[x].ch[1] = merge(c[x].ch[1], y);
            pushup(x);
            return x;
        } else {
            // y = copyNode(y);
            c[y].ch[0] = merge(x, c[y].ch[0]);
            pushup(y);
            return y;
        }
    }
}

void split(int z, int key, int &x, int &y) {
    if(!z) {
        x = y = 0;
    } else {
        z = copyNode(z); // Where counts
        if(c[c[z].ch[0]].size >= key) {
            split(c[z].ch[0], key, x, c[z].ch[0]);
            y = z;
        } else {
            split(c[z].ch[1], key - c[c[z].ch[0]].size - 1, c[z].ch[1], y);
            x = z;
        } pushup(z);
    }
}

int find(int x, int key) {
    return (c[c[x].ch[0]].size + 1 == key)
        ? x
        : (c[c[x].ch[0]].size >= key)
        ? find(c[x].ch[0], key)
        : find(c[x].ch[1], key - c[c[x].ch[0]].size - 1);
}

int n;

int cnt;

int main() {
    for(getInt >> n; n --> 0;) {
        int opt, t, k, x, u, v, w;
        getInt >> opt >> t >> k;
        if(opt == 1) {
            getInt >> x;
            split(root[++cnt] = root[t], k - 1, u, v);
            root[cnt] = merge(u, merge(newNode(x), v));
        } else if(opt == 2) {
            split(root[++cnt] = root[t], k - 1, u, v);
            split(v, 1, v, w);
            root[cnt] = merge(u, w);
        } else {
            std::printf("%d\n", c[find(root[t], k)].val);
        }
    }

    return 0;
}
