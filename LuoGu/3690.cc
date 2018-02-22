#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const size_t Size = 3e5 + 5;

int n, m;

struct Node {
    Node *fa, *ch[2];
    int val, sum;
    bool rev;

    bool isroot() {
        return fa? (fa->ch[0] != this && fa->ch[1] != this) : true;
    }

    void pushup() {
        sum = val
            ^ (ch[0]? ch[0]->sum : 0)
            ^ (ch[1]? ch[1]->sum : 0);
    }

    void reverse() {
        std::swap(ch[0], ch[1]);
        rev ^= 1;
    }

    void pushdown() {
        if(rev) {
            if(ch[0]) ch[0]->reverse();
            if(ch[1]) ch[1]->reverse();
            rev = 0;
        }
    }

    bool dir() {
        return fa? (fa->ch[1] == this) : 1;
    }
} nd[Size];

Node *stk[Size];
int cnt;

void rotate(Node *x) {
    Node *y = x->fa, *z = y->fa;
    bool d = x->dir();
    if(!y->isroot())
        z->ch[y->dir()] = x;
    y->ch[d] = x->ch[!d];
    x->ch[!d] = y;
    if(y->ch[d])
        y->ch[d]->fa = y;
    y->fa = x;
    x->fa = z;
    y->pushup();
}

void splay(Node *x) {
    Node *y = x;
    stk[++cnt] = y;
    while(!y->isroot()) stk[++cnt] = y = y->fa;
    while(cnt) stk[cnt--]->pushdown();
    while(!x->isroot()) {
        y = x->fa;
        if(!y->isroot()) rotate((x->dir() ^ y->dir())? y : x);
        rotate(x);
    } x->pushup();
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

void split(Node *x, Node *y) {
    makeroot(x);
    access(y);
    splay(y);
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

int main() {
    std::scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; ++i) std::scanf("%d", &nd[i].val);

    while(m --> 0) {
        int cmd, x, y;
        std::scanf("%d%d%d", &cmd, &x, &y);
        switch(cmd) {
        case 0:
            split(&nd[x], &nd[y]);
            std::printf("%d\n", nd[y].sum);
            break;
        case 1:
            link(&nd[x], &nd[y]);
            break;
        case 2:
            cut(&nd[x], &nd[y]);
            break;
        case 3:
            splay(&nd[x]);
            nd[x].val = y;
        }
     }

    return 0;
}
