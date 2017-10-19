#include <cstdio>
#include <iostream>
#include <set>
#include <algorithm>
#include <cstring>

// const int Inf = -1u >> 1;
const size_t Size = 2e5 + 5;

template<class T> T max(const T &a, const T &b) {
    return a >= b? a : b;
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
    T r(0); char c(getchar()); bool n(0);
    while(c > '9' || c < '0') {if(c == '-') n = 1; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

std::multiset<int> tr[Size];

struct Data {int x, w, p; bool sign;} q[Size];

int n, m;

int dex[Size << 1], lim;
int w[Size], p[Size];

struct interval_tree {
  std::pair<int, int> c[Size << 1 << 2];

    void pull(int i) {
        c[i] = ::max(c[i << 1], c[i << 1|1]);
    }

    void update(int i, int l, int r, int pos, int key) {
        if(l == r) {
            c[i] = std::make_pair(key, l);
        } else {
            int mid = (l + r) >> 1;
            if(pos <= mid) update(i << 1, l, mid, pos, key);
            else update(i << 1|1, mid + 1, r, pos, key);
            pull(i);
        }
    }

    std::pair<int, int>
        query(int i, int l, int r, int s, int t) {
        // std::cerr << __LINE__ << std::endl;
        if(l >= s && r <= t) {
            return c[i];
        } else {
            int mid = (l + r) >> 1;
            if(s > mid) return query(i << 1|1, mid + 1, r, s, t);
            else if(t <= mid) return query(i << 1, l, mid, s, t);
            else return ::max(query(i << 1, l, mid, s, mid),
                              query(i << 1|1, mid + 1, r, mid + 1, t));
        }
    }
} T;

int main() {
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);

    n = input<int>(), m = input<int>();

    for(int i = 1; i <= n; ++i) {
        w[i] = input<int>(), p[i] = input<int>();
        dex[++lim] = p[i];
    }

    for(int i = 1; i <= m; ++i) {
        if((q[i].sign = (input<int>() == 1))) {
            q[i].x = input<int>();
            q[i].w = input<int>();
            q[i].p = input<int>();
            dex[++lim] = q[i].p;
        } else q[i].x = input<int>();
    }

    std::sort(dex + 1, dex + 1 + lim);
    lim = std::unique(dex + 1, dex + 1 + lim) - dex - 1;

    for(int i = 1, x; i <= n; ++i) {
        x = std::lower_bound(dex + 1, dex + 1 + lim, p[i]) - dex;
        if(tr[x].empty() || *tr[x].rbegin() < w[i]) T.update(1, 1, lim, x, w[i]);
        tr[x].insert(w[i]);
    }

    //for(int i = 1; i <= n; ++i) if(T.query(1, 1, ))

    for(int i = 1, x, u; i <= m; ++i)
        if(q[i].sign) {
            x = std::lower_bound(dex + 1, dex + 1 + lim, p[q[i].x]) - dex;
            if(tr[x].find(w[q[i].x]) == tr[x].end()) throw;
            tr[x].erase(tr[x].find(w[q[i].x])), u = tr[x].empty()? 0 : *tr[x].rbegin();
            // std::cerr << __LINE__ << std::endl;
            T.update(1, 1, lim, x, u), w[q[i].x] = q[i].w, p[q[i].x] = q[i].p;
            x = std::lower_bound(dex + 1, dex + 1 + lim, p[q[i].x]) - dex;
            if(tr[x].empty() || *tr[x].rbegin() < w[q[i].x]) T.update(1, 1, lim, x, w[q[i].x]);
            tr[x].insert(w[q[i].x]);
        } else {
            static long long ans; ans = 0;
            static std::pair<int, int> tmp;
            do {
                x = std::upper_bound(dex + 1, dex + 1 + lim, q[i].x) - dex - 1;
                if(x < 1) break;
                tmp = T.query(1, 1, lim, 1, x);
                if(!tmp.first) break;
                ans += (long long)(q[i].x / dex[tmp.second]) * tmp.first;
                q[i].x %= dex[tmp.second];
            } while(tmp.first);
            printf("%lld\n", ans);
        }

    return 0;
}
