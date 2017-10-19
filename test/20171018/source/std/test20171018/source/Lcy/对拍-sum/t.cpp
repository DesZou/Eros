#include<cstdio>

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
static const int maxn = 1e5 + 11 ;

int n ;
LL mod ;
LL mul ;
LL ans ;

int ai[maxn] ;

inline LL add (LL x, LL y) {
	x += y ; if (x >= mod) x -= mod ; return x ;
}

inline LL qmul (LL x, LL y) {
	LL res = 0LL ;
	for (; y ; y >>= 1, x = add (x, x) )
		if (y & 1) res = add (res, x) ;
	return res ;
}

int main() {
	
	freopen ("t.in", "r", stdin) ;
	freopen ("t.out", "w", stdout) ;
	
	scanf(n) ; scanf(mod) ;
	FOR (i, 1, n) scanf(ai[i]), ai[i] %= mod ;
	
	FOR (i, 1, n) {
		mul = qmul (add (mul, 1LL), ai[i]) ;
		ans = add (ans, mul) ;
	}
	
	printf ("%lld\n", ans) ;
	
	return 0 ;
}
