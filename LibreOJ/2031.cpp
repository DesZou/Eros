#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

const long long Inf = LONG_MAX;
const int size = 400 + 5;

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
    T res = 0; char c = getchar(); bool nega = 0;
    while(c < '0' || c > '9') {if(c == '-') nega = 1; c = getchar();}
    while(c <= '9' && c >= '0') {res = res * 10 - 48 + c, c = getchar();}
    return nega? -res : res;
}

namespace MincostMaxflow {
    struct Curve {
        int next, to;
        long long cap, cost;
    } c[(size * size) << 2];

    int source, sink;

    long long _Mincost, _Maxflow;

    int head[size], path[size];
    long long dis[size];

    bool spfa() {
        std::memset(dis, 127, sizeof dis);
        static std::deque<int> q;
        static bool in_q[size];
        dis[source] = 0, q.push_back(source);

        while(!q.empty()) {
            int now = q.front(); q.pop_front(); in_q[now] = false;
            for(int i = head[now]; i; i = c[i].next) {
                if(c[i].cap && chkmin(dis[c[i].to], dis[now] + c[i].cost)) {
                    path[c[i].to] = i;
                    if(!in_q[c[i].to]) {
                        in_q[c[i].to] = true;
                        if(dis[c[i].to] < q.front()) q.push_front(c[i].to);
                        else q.push_back(c[i].to);
                    }
                }
            }
        } return dis[sink] < Inf / 2;
    }

    bool addFlow() {
        long long low = Inf;
        for(int now = sink; now != source; now = c[path[now] ^ 1].to)
            chkmin(low, c[path[now]].cap);
        if(_Mincost + low * dis[sink] > 0)
            {_Maxflow += -_Mincost / dis[sink]; return false;}
        _Mincost += low * dis[sink];
        _Maxflow += low;
        for(int now = sink; now != source; now = c[path[now] ^ 1].to)
            c[path[now]].cap -= low, c[path[now] ^ 1].cap += low;
        return true;
    }

    inline long long figure() {
        while(spfa() && addFlow());
        std::cerr << _Mincost << std::endl;
        return _Maxflow;
    }

    void insert(int u, int v, long long w, long long x) {
        static int _Index = 1;
        c[++_Index] = (Curve){head[u], v, w, x};
        head[u] = _Index;
    }
};

int n;

int a[size], b[size];
long long c[size];

int prime[300000 + 5], total;

bool notPrime[300000 + 5];

void init() {
    for(int i = 2; i <= 300000 + 5; ++i) {
        if(!notPrime[i]) prime[++total] = i;
        for(int j = 1; i * prime[j] <= 300000 + 5; ++j) {
            notPrime[i * prime[j]] = true;
            if(i % prime[j] == 0) break;
        }
    }
}

bool count(int x) {
    int res = 0;
    for(int i = 1, j; i <= total && prime[i] <= x; ++i) {
        j = prime[i];
        while(x % j == 0) x /= j, ++res;
    } return res & 1;
}

bool check(int x, int y) {
    if(x < y) std::swap(x, y);
    if(x % y == 0) {
        for(int i = 1; prime[i] <= x / y; ++i)
            if(prime[i] == x / y) return true;
        return false;
    } else return false;
}

int main() {
    using namespace MincostMaxflow;

    init();
    
    n = input<int>();

    source = n + 1, sink = n + 2;

    for(int i = 1; i <= n; ++i) a[i] = input<int>();
    for(int i = 1; i <= n; ++i) b[i] = input<int>();
    for(int i = 1; i <= n; ++i) ::c[i] = input<int>();

    for(int i = 1; i <= n; ++i) {
        if(count(a[i])) {
            insert(source, i, b[i], 0);
            insert(i, source, 0, 0);

            for(int j = 1; j <= n; ++j) if(i != j) {
                if(check(a[i], a[j])) {
                    insert(i, j, Inf, -::c[i] * ::c[j]);
                    insert(j, i, 0, ::c[i] * ::c[j]);
                }
            }
        } else {
            insert(i, sink, b[i], 0);
            insert(sink, i, 0, 0);
        }
    }

    printf("%lld\n", figure());

    return 0;
}
