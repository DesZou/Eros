#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using std :: pair ;

#define For(i, _begin, _end) \
for (int i = (_begin), i##end = (_end) ; i <= (i##end) ; ++i)
#define Lop(i, _begin, _end) \
for (int i = (_begin), i##end = (_end) ; i >= (i##end) ; --i)
#define Rep(i, _begin, _add) \
for (int i = (_begin) ; i ; i = (_add))
#define FOR(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end) ; i <= (i##end) ; ++i)
#define LOP(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end) ; i >= (i##end) ; --i)
#define REP(i, _begin, _add) \
for (register int i = (_begin) ; i ; i = (_add))

template <typename tp>
inline tp max (const tp& x, const tp& y) { return (x > y)? x: y ; }
template <typename tp>
inline tp min (const tp& x, const tp& y) { return (x < y)? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, const tp& y) {
	return (x >= y)? (false): (x = y, true) ;
}
template <typename tp>
inline bool chkmin (tp& x, const tp& y) {
	return (x <= y)? (false): (x = y, true) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for (; ch> '9' || ch< '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 2e5 + 11 ;

class shop {
	public :
		int w ;
		int p ;
		
		shop () { w = p = 0 ; }
		shop (int a, int b) { w = a ; p = b ; }
		
		bool operator < (const shop& x) const {
			if (w != x.w) return w > x.w ;
			return p < x.p ;
		}
} ;

int n ;
int m ;
int cnt ;
int root ;

shop bt[maxn] ;

shop val[maxn] ;

int mn[maxn] ;
int sz[maxn] ;
int fix[maxn] ;
int Ch[maxn][2] ;

inline void up (int x) {
	sz[x] = sz[Ch[x][0]] + sz[Ch[x][1]] + 1 ;
	mn[x] = min (min (mn[Ch[x][0]], mn[Ch[x][1]]), val[x].p) ;
}

int merge (int x, int y) {
	if (!x || !y) return x ^ y ;
	if (fix[x] > fix[y]) {
		Ch[x][1] = merge (Ch[x][1], y) ;
		return up (x), x ;
	} else {
		Ch[y][0] = merge (x, Ch[y][0]) ;
		return up (y), y ;
	}
}

pair <int, int> split(int x, int y) {
	if (!x) return pair <int, int> (0, 0) ;
	pair <int, int> res ;
	if (sz[Ch[x][0]] >= y) {
		res = split (Ch[x][0], y) ;
		Ch[x][0] = res.second ; res.second = x ;
	} else {
		res = split (Ch[x][1], y - sz[Ch[x][0]] - 1) ;
		Ch[x][1] = res.first ; res.first = x ;
	}
	return up (x), res ;
}

inline int find (shop key) {
	int rt = root, res = 0 ;
	while (rt)
		if (key < val[rt]) rt = Ch[rt][0] ;
		else res += sz[Ch[rt][0]] + 1, rt = Ch[rt][1] ;
	return res ;
}

inline shop finder (int x) {
	int rt = root ; shop res ;
	while (rt)
		if (mn[Ch[rt][0]] <= x && Ch[rt][0]) rt = Ch[rt][0] ;
		else {
			if (val[rt].p <= x && res.w < val[rt].w) res = val[rt] ;
			rt = Ch[rt][1] ;
		}
	return res ;
}

inline int newone (shop key) {
	int x = ++cnt ;
	sz[x] = 1 ; fix[x] = rand() ; mn[x] = key.p, val[x] = key ; return x ;
}

inline void insert (shop x) {
	if (!root ) return root = newone (x), void() ;
	int t = find (x), rt = newone (x) ;
	pair <int, int> p = split (root, t) ;
	root = merge (merge (p.first, rt), p.second) ;
}

inline void del (shop x) {
	int t = find (x) ;
	pair <int, int> p1 = split (root, t - 1) ;
	pair <int, int> p2 = split (p1.second, 1) ;
	root = merge (p1.first, p2.second) ;
}

inline LL query (int k) {
	LL res = 0LL ;
	while (k) {
		shop t = finder (k) ;
		if (!t.p) break ;
		res += 1LL * (k / t.p) * t.w ;
		k %= t.p ;
	}
	return res ;
}

int main() {
	
	freopen ("t.in", "r", stdin) ;
	freopen ("t.out", "w", stdout) ;
	
	srand (time(NULL)) ;
	
	memset (mn, 0x7f, sizeof mn) ;
	
	scanf(n) ; scanf(m) ;
	FOR (i, 1, n) scanf(bt[i].w), scanf(bt[i].p), insert (bt[i]) ;
	
	while (m--) {
		int op, x, w, p ;
		scanf(op) ; scanf(x) ;
		if (op == 1) {
			scanf(w) ; scanf(p) ;
			del (bt[x]) ; bt[x] = shop (w, p) ;
			insert (bt[x]) ;
		} else printf ("%lld\n", query (x)) ;
	}
	
	return 0 ;
}
