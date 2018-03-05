#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using std::cerr;
using std::endl;
using std::max;
using std::min;
using std::swap;

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

const int Size = 8e4 + 5;

struct Node {
    Node *fa, *ch[2];
    int val, size;

    bool operator!() { return fa && fa->ch[1] == this; }

    void pushup() {
        size = 1
            + (ch[0]? ch[0]->size : 0)
            + (ch[1]? ch[1]->size : 0);
    }

    int rank() { return 1 + (ch[0]? ch[0]->size : 0); }

    Node(int v): val(v), size(1) { fa = ch[0] = ch[1] = NULL; }
} *root;

void rotate(Node *x) {
    Node *y = x->fa;
    bool d = !*x;
    if (x->ch[!d]) x->ch[!d]->fa = y;
    y->ch[d] = x->ch[!d];
    if (y->fa) y->fa->ch[!*y] = x;
    x->fa = y->fa;
    x->ch[!d] = y;
    y->fa = x;
    y->pushup();
    x->pushup();
}

void splay(Node *x, Node *tar = NULL) {
    for (Node *y = x->fa; y != tar; y = x->fa) {
        if (y->fa != tar) rotate(!*y == !*x? y : x);
        rotate(x);
    }
    if (x->fa == NULL) root = x;
}

Node* find(Node *x, int key) {
    return x->rank() == key
        ? x
        : (x->rank() > key)
        ? find(x->ch[0], key)
        : find(x->ch[1], key - x->rank());
}

Node* pred(Node *x) {
    splay(x);
    return x->ch[0]? find(x->ch[0], x->ch[0]->size) : NULL;
}

Node* succ(Node *x) {
    splay(x);
    return x->ch[1]? find(x->ch[1], 1) : NULL;
}

void traversal(Node *x) {
    assert(!x->ch[0] || x->ch[0]->fa == x);
    assert(!x->ch[1] || x->ch[1]->fa == x);
    if (x->ch[0]) traversal(x->ch[0]);
    cerr << " " << x->val;
    if (x->ch[1]) traversal(x->ch[1]);
}

Node *ptr[Size];

int n, m;

int main() {
    getInt >> n >> m;

    for (int i = 1, x; i <= n; ++i) {
        getInt >> x;
        ptr[x] = new Node(x);
        ptr[x]->ch[0] = root;
        if (root) root->fa = ptr[x];
        root = ptr[x];
        ptr[x]->pushup();
    }

    char cmd[10];
    Node *x;
    for (int i = 1, s, t; i <= m; ++i) {
        scanf("%s", cmd);
        // cerr << cmd << " |";
        // traversal(root);
        // cerr << endl;
        getInt >> s;
        switch (*cmd) {
        case 'T': // TOP
            x = succ(ptr[s]);
            if (!x) {
                ptr[s]->ch[1] = ptr[s]->ch[0];
                ptr[s]->ch[0] = NULL;
                break;
            }
            x->ch[0] = ptr[s]->ch[0];
            if (x->ch[0]) x->ch[0]->fa = x;
            ptr[s]->ch[0] = NULL;
            splay(x);
            break;
        case 'B': // BOTTOM
            x = pred(ptr[s]);
            if (!x) {
                ptr[s]->ch[0] = ptr[s]->ch[1];
                ptr[s]->ch[1] = NULL;
                break;
            }
            x->ch[1] = ptr[s]->ch[1];
            if (x->ch[1]) x->ch[1]->fa = x;
            ptr[s]->ch[1] = NULL;
            splay(x);
            break;
        case 'I': // INSERT
            getInt >> t;
            if (!t) break;
            x = t == 1? succ(ptr[s]) : pred(ptr[s]);
            swap(x->val, ptr[s]->val);
            swap(ptr[x->val], ptr[ptr[s]->val]);
            break;
        case 'A': // ASK
            splay(ptr[s]);
            printf("%d\n", ptr[s]->rank() - 1);
            break;
        case 'Q': // QUERY
            x = find(root, s);
            printf("%d\n", x->val);
            splay(x);
            break;
        default:
            return -1;
        }
    }

    return 0;
}
