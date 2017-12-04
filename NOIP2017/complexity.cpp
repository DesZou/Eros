#include <cstdio>
#include <stack>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstring>

#define N -1

const size_t Length = 100 + 5;
const int Err = 1e9 + 7;

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

int sinput(char* &s) {
    int res = 0;
    while(*s > '9' || *s < '0') {if(*s++ == 'n') return -1;}
    while(*s <= '9' && *s >= '0') {res = res * 10 - 48 + *s++;}
    return res;
}

struct Edge {int next, to;} e[1000];

char str[Length], *ptr;

int ans, a, b, nodenum;

std::stack<char> s;

bool table[500];

int num[500];

int head[500], val[500];

void insert(int u, int v) {
    static int _Index = 0;
    e[++_Index] = (Edge){head[u], v};
    head[u] = _Index;
}

void search(int x, int num = 0) {
    // std::cerr << x << " " << val[x] << std::endl;
    if(val[x] == 1) ++num;
    chkmax(ans, num);
    if(val[x] != -1)
        for(int i = head[x]; i; i = e[i].next)
            search(e[i].to, num)/*, std::cerr << x << " -> " << e[i].to << std::endl*/;
}

int main() {
    // freopen("complexity.in", "r", stdin);
    // freopen("complexity.out", "w", stdout);

    for(int T = input<int>(), L; T --> 0;) {
        std::memset(table, 0, sizeof table);
        std::memset(head, 0, sizeof head);
        while(!s.empty()) s.pop();
        s.push(1);
        ans = 0, num[1] = nodenum = 1;
        fgets(str, Length, stdin);
        ptr = str;
        L = sinput(ptr);
        a = sinput(ptr);
        b = a == N? sinput(ptr) : 0;
        while(L --> 0) {
            fgets(str, Length, stdin);
            ptr = str + 1;
            if(*str == 'F') {
                char c;
                do {c = *ptr++;} while(c < 'a' || c > 'z');
                if(table[c] == true) ans = Err;
                table[c] = true, num[c] = ++nodenum;
                int x = sinput(ptr);
                int y = sinput(ptr);
                insert(num[s.top()], num[c]);
                if(x != N && y == N) val[num[c]] = 1;
                else if(x == N && y != N) val[num[c]] = -1;
                else if(x != N && y != N && x > y) val[num[c]] = -1;
                else val[num[c]] = 0;
                s.push(c);
             } else if(*str == 'E') {
                if(s.size() == 1) ans = Err;
                else {
                    table[s.top()] = false;
                    s.pop();
                }
            }
        }
        if(ans == Err || s.size() != 1) puts("ERR");
        else search(1), puts(ans == b? "Yes" : "No");
        // std::cerr << "ans := " << ans << std::endl;
    }

    return 0;
}
