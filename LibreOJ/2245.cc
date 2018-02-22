/*
 *  libreoj2245
 *
 *  LCT 维护最大值。
 *  首先把边按 a 权值排序，从小到大加入，那么所需的 a 就是当前边的 a 。
 *  然后用 LCT 维护从 1 到 n 的路径的 b 权值的最大值。
 *  由于维护的是边权，我们要给边特别地开点，然后把本来应该相连的点连到两边。
 *  动态维护一棵最小生成树，每次加入一条从 u 到 v 的路径的时候就把原来的
 *  u, v 之间的路径拉出来查询一下路径上的最大值，如果比当前的边要大，
 *  就把代表这条边的点从路径里拿出来，再把新边放进去。
 * */
#include <cstdio>
#include <algorithm>
#include <iostream>

const size_t Size = 5e4 + 5;
const int Inf = -1u >> 1;

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
    return a <b? a = b, 1 : 0;
}

struct IM { template<class T> IM& operator>>(T &a) {
    a = 0; char c = getchar(); bool n = false;
    for(;!isdigit(c); c = getchar()) if(c == '-') n = 1;
    for(; isdigit(c); c = getchar()) a = a * 10 - 48 + c;
    if(n) a = -a;
    return *this;
} } getInt;

struct UnionFindSet {
    int fa[Size * 4];

    void init(int x) {
        for(int i = 1; i <= x; ++i) fa[i] = i;
    }

    int find(int x) {
        return x == fa[x]? x : fa[x] = find(fa[x]);
    }

    int& operator[](const int &x) {
        return fa[x];
    }
} set;

struct Edge {
    int u, v, a, b;
} e[Size * 2];

bool operator<(const Edge &a, const Edge &b) {
    return a.a < b.a;
}

struct Node {
    int val, id;
    Node *fa, *ch[2], *mx;
    bool rev;

    bool isroot() {
        return fa? (fa->ch[0] != this && fa->ch[1] != this) : true;
    }

    void pushup() {
        mx = this;
        if(ch[0] && ch[0]->mx->val > mx->val) mx = ch[0]->mx;
        if(ch[1] && ch[1]->mx->val > mx->val) mx = ch[1]->mx;
    }

    void reverse() {
        rev ^= 1;
        std::swap(ch[0], ch[1]);
    }

    void pushdown() {
        if(rev) {
            if(ch[0]) ch[0]->reverse();
            if(ch[1]) ch[1]->reverse();
            rev = 0;
        }
    }

    bool operator!() {
        return fa->ch[1] == this;
    }
} nd[Size * 4];

void rotate(Node *x) {
    Node *y = x->fa;
    bool d = !*x; // must take care here, !*x IS NOT !x
    if(!y->isroot())
        y->fa->ch[!*y] = x;
    x->fa = y->fa;
    y->fa = x;
    y->ch[d] = x->ch[!d];
    x->ch[!d] = y;
    if(y->ch[d])
        y->ch[d]->fa = y;
    y->pushup();
    x->pushup();
}

void push(Node *x) {
    if(!x->isroot()) push(x->fa);
    x->pushdown();
}

void splay(Node *x) {
    push(x);

    for(Node *y = x->fa; !x->isroot(); y = x->fa) {
        if(!y->isroot()) rotate(!*x == !*y? y : x);
        rotate(x);
    }
}

void access(Node *x) {
    for(Node *y = NULL; x; x = (y = x)->fa) {
        splay(x);
        x->ch[1] = y;
        x->pushup();
    }
}

void makeroot(Node *x) {
    access(x);
    splay(x);
    x->reverse();
}

Node* findroot(Node *x) {
    access(x);
    splay(x);
    while(x->ch[0]) x = x->ch[0];
    return x;
}

void link(Node *x, Node *y) {
    makeroot(x);
    if(findroot(y) != x) x->fa = y;
}

void cut(Node *x, Node *y) {
    makeroot(x);
    if(findroot(y) == x && x->fa == y && x->ch[1] == NULL) {
        x->fa = y->ch[0] = NULL;
        y->pushup();
    }
}

void split(Node *x, Node *y) {
    makeroot(x);
    access(y);
    splay(y);
}

int query(int x, int y) {
    split(&nd[x], &nd[y]);
    return nd[y].mx->val;
}

int n, m;

int ans = Inf;

int main() {
    getInt >> n >> m;

    set.init(n);

    for(int i = 1; i <= m; ++i) {
        getInt >> e[i].u >> e[i].v >> e[i].a >> e[i].b;
    }

    std::sort(e + 1, e + 1 + m);

    for(int i = 1, u, v, a, b; i <= m; ++i) {
        u = e[i].u, v = e[i].v, a = e[i].a, b = e[i].b;
        if(set.find(u) == set.find(v)) {
            split(&nd[u], &nd[v]);
            Node *x = nd[v].mx;
            if(x->val > b) {
                cut(x, &nd[e[x->id].u]);
                cut(x, &nd[e[x->id].v]);
            } else {
                // if(set.find(1) == set.find(n)) chkmin(ans, a + query(1, n));
                continue;
            }
        } else {
            set[set[u]] = set[v];
        }
        nd[n + i].val = b;
        nd[n + i].mx = &nd[n + 1];
        nd[n + i].id = i;
        link(&nd[u], &nd[n + i]);
        link(&nd[v], &nd[n + i]);
        if(set.find(1) == set.find(n)) chkmin(ans, a + query(1, n));
    }

    std::printf("%d\n", ans == Inf? -1 : ans);

    return 0;
}
